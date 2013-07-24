#include <Survive/world.h>
#include <Survive/math_utils.h>
#include <Survive/debug_render.h>
#include <Survive/content_manager.h>
#include <Survive/collision/ray.h>

#include <Survive/scene_nodes/scene_node.h>
#include <Survive/scene_nodes/landscape_node.h>
#include <Survive/scene_nodes/player_entity_node.h>
#include <Survive/scene_nodes/monster_entity_node.h>
#include <Survive/scene_nodes/respawn_node.h>
#include <Survive/scene_nodes/static_sprite_node.h>
#include <Survive/scene_nodes/static_convex_node.h>

#include <Survive/templates/template_manager.h>
#include <Survive/templates/player_template.h>
#include <Survive/templates/monster_template.h>
#include <Survive/templates/respawn_template.h>
#include <Survive/templates/static_sprite_template.h>
#include <Survive/templates/static_convex_template.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window.hpp>

#include <math.h>

namespace Survive
{

template <class NodeT, class TemplateT>
void GenerateObjects(World* pWorld, int ObjectC, const std::string& TemplateName)
{
	for (int Idx = 0; Idx < ObjectC; ++Idx)
	{
		sf::Vector2f Pos;
		Pos.x = MathUtils::RandomRange(0, pWorld->GetWorldBound().GetSize().x);
		Pos.y = MathUtils::RandomRange(0, pWorld->GetWorldBound().GetSize().y);

		NodeT* pNode = pWorld->CreateNode<NodeT>(pWorld->GetLayerRoot(eWorldLayer::GroundLayer));
		TemplateT* pNodeTmpl = TemplateManager::Instance().GetTemplate<TemplateT>(TemplateName);
		pNode->InitFromTemplate(pNodeTmpl);
		Pos = pWorld->ConstrainToWorld(Pos, pNode->GetBounds().GetSize() * 0.5f);
		pNode->SetLocalPosition(Pos);

		QuadTreeNode::HitList Objects;

		unsigned int CollisionMask = eCollisionGroup::Characters | eCollisionGroup::Static | eCollisionGroup::Respawn;
		pWorld->GetQuadTree()->GetObjects(pNode->GetBounds(), pNode->GetWorldTransform(), CollisionMask, 0, Objects);

		while (!Objects.empty())
		{
			if(Objects.size() == 1 && Objects[0].m_pObject == pNode)
				break;

			Objects.clear();
			sf::Vector2f Pos;
			sf::Vector2f HalfSize = pNode->GetBounds().GetSize() * 0.5f;
			Pos.x = MathUtils::RandomRange(0, pWorld->GetWorldBound().GetSize().x);
			Pos.y = MathUtils::RandomRange(0, pWorld->GetWorldBound().GetSize().y);
			Pos = pWorld->ConstrainToWorld(Pos + HalfSize, HalfSize);
			pNode->SetLocalPosition(Pos);
			pWorld->GetQuadTree()->GetObjects(pNode->GetBounds(), pNode->GetWorldTransform(), CollisionMask, 0, Objects);
		}
	}
}

World::World(Context* pContext)
	:
m_pContext(pContext),
m_pPlayer(0),
m_TickCounter(0)
{
	m_View = m_pContext->GetRenderWindow()->getDefaultView();
	m_pSceneRoot.reset(CreateNode<SceneNode>(0));
}

World::~World()
{
	m_pSceneRoot.reset(0);
	m_pQuadTree.reset(0);
}

void World::Init()
{
	for (size_t Idx = 0; Idx < m_pLayers.size(); ++Idx)
	{
		m_pLayers[Idx] = CreateNode<SceneNode>(GetSceneRoot());

		m_pLayers[Idx]->m_Layer = (eWorldLayer::Val)Idx;
	}

	for (size_t Idx = eTextureID::ChaosLordBody; Idx < eTextureID::TextureCount; ++Idx)
	{
		m_pContext->GetContentManager()->LoadTexture((eTextureID::Val)Idx);
	}

	const BigTexture* LandscapeTex = m_pContext->GetContentManager()->LoadBigTexture(eBigTextureID::Landscape);
	sf::Vector2u texSize = LandscapeTex->GetSize();
	m_WorldBound.SetSize(sf::Vector2f(texSize.x, texSize.y));

	m_pQuadTree.reset(new QuadTreeNode(m_WorldBound, 0, 1, 0));

	LandscapeNode* Landscape = CreateNode<LandscapeNode>(GetLayerRoot(eWorldLayer::LandscapeLayer));
	Landscape->SetTexture(LandscapeTex);

	m_pPlayer = CreateNode<PlayerEntityNode>(GetLayerRoot(eWorldLayer::GroundLayer));
	PlayerTemplate* pPlayerTmpl = TemplateManager::Instance().GetTemplate<PlayerTemplate>("Player");
	m_pPlayer->InitFromTemplate(pPlayerTmpl);
	m_pPlayer->SetLocalPosition(sf::Vector2f(100.0f, 100.0f));

	GenerateObjects<StaticSpriteEntityNode, StaticSpriteTemplate>(this, 10, "StaticSprites");
	GenerateObjects<StaticConvexEntityNode, StaticConvexTemplate>(this, 10, "StaticConvexes");
	GenerateObjects<RespawnEntityNode, RespawnTemplate>(this, 200, "MonsterRespawn");
}

void World::Update(float Dt)
{
	RemoveNodes();
	GetContext()->GetDebugRender()->Update(Dt);
	size_t ObjC = m_pQuadTree->GetObjectCount();

	++m_TickCounter;

	float ScrollSpeed = m_pPlayer->GetSpeed();
	sf::Vector2f MoveDisp;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		MoveDisp.y = -ScrollSpeed * Dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		MoveDisp.y = ScrollSpeed * Dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		MoveDisp.x = -ScrollSpeed * Dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		MoveDisp.x = ScrollSpeed * Dt;
	}
	
	if (MoveDisp.x && MoveDisp.y)
	{
		MoveDisp *= 1.0f / sqrtf(2.0f);
	}

	m_pPlayer->DynamicMove(MoveDisp, true);

	AlignedBoxShape PlayerBounds = m_pPlayer->GetBounds();
	sf::Vector2f PlayerHalfSize(PlayerBounds.GetSize() * 0.5f);
	sf::Vector2f pl = m_pPlayer->GetLocalPosition();
	sf::Vector2f pw = m_pPlayer->GetWorldPosition();
	m_pPlayer->SetLocalPosition(ConstrainToWorld(m_pPlayer->GetLocalPosition(), PlayerHalfSize));

	m_View.setCenter(m_pPlayer->GetWorldPosition());

	sf::Vector2i MousePos = sf::Mouse::getPosition(*GetContext()->GetRenderWindow());
	sf::Vector2f WorldPos = GetContext()->GetRenderWindow()->mapPixelToCoords(MousePos);
	sf::Vector2f Delta = WorldPos - m_pPlayer->GetLocalPosition();

	GetContext()->GetDebugRender()->AddLine(LineSegment(m_pPlayer->GetLocalPosition(), WorldPos), 0.01f);

	Delta = MathUtils::Normalize(Delta);

	HitInfo Trace;
	m_pQuadTree->RayTraceClosest(Ray(m_pPlayer->GetWorldPosition(), Delta), eCollisionGroup::Monster | eCollisionGroup::Static, m_pPlayer, Trace);

	if (Trace.m_pObject)
	{
		sf::Vector2f HitPos = m_pPlayer->GetWorldPosition() + Delta * Trace.m_Param;
		GetContext()->GetDebugRender()->AddCircle(HitPos, 10.0f, 0.01f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_pPlayer->UseRangedWeapon(Delta);
	}

	m_pPlayer->SetLocalRotation( MathUtils::RadToDeg(atan2f(Delta.y, Delta.x)) + 45.0f);

	m_View.setCenter(ConstrainToWorld(m_View.getCenter(), m_View.getSize() * 0.5f));

	m_pSceneRoot->Update(Dt);
}

void World::Draw(sf::RenderWindow* Window)
{
	Window->setView(m_View);
	//Window->draw(*m_pSceneRoot);

	sf::Vector2f ViewPos = m_View.getCenter();
	sf::Vector2f ViewSize = m_View.getSize();

	AlignedBoxShape ViewBox(ViewPos - ViewSize * 0.5f, ViewSize);
	m_InViewObjects.clear();
	GetQuadTree()->GetObjects(ViewBox, sf::Transform::Identity, eCollisionGroup::All, 0, m_InViewObjects);

	std::sort(m_InViewObjects.begin(), m_InViewObjects.end(), 
		[](const HitInfo& Hit1, const HitInfo& Hit2)->bool
		{
			return Hit1.m_pObject->GetWorldLayer() < Hit2.m_pObject->GetWorldLayer();
		}
		);

	for (size_t Idx = 0; Idx < m_InViewObjects.size(); ++Idx)
	{
		Window->draw(*m_InViewObjects[Idx].m_pObject);
	}

	GetContext()->GetDebugRender()->Draw(Window);
	
}

sf::Vector2f World::ConstrainToWorld(const sf::Vector2f& Center, const sf::Vector2f& HalfSize)
{
	sf::Vector2f Result(Center);

	sf::Vector2f TopLeft = Center - HalfSize;
	sf::Vector2f BottomRight = Center + HalfSize;

	if (TopLeft.x < 0.0f)
	{
		Result.x = HalfSize.x;
	}
	else if (BottomRight.x > m_WorldBound.GetSize().x)
	{
		Result.x = m_WorldBound.GetSize().x - HalfSize.x;
	}

	if (TopLeft.y < 0.0f)
	{
		Result.y = HalfSize.y;
	}
	else if (BottomRight.y > m_WorldBound.GetSize().y)
	{
		Result.y = m_WorldBound.GetSize().y - HalfSize.y;
	}

	return Result;
}

unsigned int World::RequestUpdatePhase(PhaseMap& PhasesMap, unsigned int Frequency, unsigned int MaxPhase)
{
	PhaseMap::iterator it = PhasesMap.find(Frequency);

	if (it != PhasesMap.end())
	{
		unsigned int nextPhase = it->second + 1;

		if(nextPhase > MaxPhase)
		{
			nextPhase = 0;
			it->second = 0;
		}
		else
		{
			it->second = nextPhase;
		}

		return nextPhase;
	}
	else
	{
		PhasesMap[Frequency] = 0;
		return 0;
	}
}

void World::AddSceneNodeToRemove(SceneNode* pSceneNode)
{
	m_SceneNodesToRemove.insert(pSceneNode);
	pSceneNode->m_Flags |= eSceneNodeFlags::MarkToDelete;
}

void World::UnregisterNode(SceneNode* pSceneNode)
{

	if (pSceneNode->m_pQuadTreeNode)
		pSceneNode->m_pQuadTreeNode->Remove(pSceneNode);

	Type* NodeType = pSceneNode->GetType();

	if (NodeType != TypeImpl<SceneNode>::Instance())
		m_TypeNodeCache[NodeType].erase(pSceneNode);
}

void World::RemoveNodes()
{
	typedef std::unordered_set<SceneNode*>::iterator iterator;

	for (iterator It = m_SceneNodesToRemove.begin(); It != m_SceneNodesToRemove.end(); ++It)
	{
		SceneNode* pNode = *It;
		SceneNode* pNodeParent = pNode->m_pParent;

		if (!pNodeParent->IsMarkedForDelete())
		{
			for (size_t ChildIdx = 0; ChildIdx < pNode->m_pChildren.size(); ++ChildIdx)
			{
				if (!pNode->m_pChildren[ChildIdx]->IsMarkedForDelete())
				{
					pNodeParent->AddChild(pNode->m_pChildren[ChildIdx].release());
				}
			}
		}

		pNodeParent->RemoveNode(pNode);
	}

	m_SceneNodesToRemove.clear();
}

bool World::IsObjectInView(SceneNode* pSceneNode)const
{
	for (size_t Idx = 0; Idx < m_InViewObjects.size(); ++Idx)
	{
		if (m_InViewObjects[Idx].m_pObject == pSceneNode)
		{
			return true;
		}
	}

	return false;
}

}