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
		pWorld->GetQuadTree()->GetObjects(pNode->GetBounds(), pNode->GetWorldTransform(), CollisionMask, Objects);

		while (!Objects.empty())
		{
			if(Objects.size() == 1 && Objects[0].m_Object == pNode)
				break;

			Objects.clear();
			sf::Vector2f Pos;
			sf::Vector2f HalfSize = pNode->GetBounds().GetSize() * 0.5f;
			Pos.x = MathUtils::RandomRange(0, pWorld->GetWorldBound().GetSize().x);
			Pos.y = MathUtils::RandomRange(0, pWorld->GetWorldBound().GetSize().y);
			Pos = pWorld->ConstrainToWorld(Pos + HalfSize, HalfSize);
			pNode->SetLocalPosition(Pos);
			pWorld->GetQuadTree()->GetObjects(pNode->GetBounds(), pNode->GetWorldTransform(), CollisionMask, Objects);
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

	GenerateObjects<StaticSpriteNode, StaticSpriteTemplate>(this, 10, "StaticSprites");
	GenerateObjects<StaticConvexNode, StaticConvexTemplate>(this, 10, "StaticConvexes");
	size_t ObjC = m_pQuadTree->GetObjectCount();
	GenerateObjects<RespawnNode, RespawnTemplate>(this, 50, "MonsterRespawn");
	ObjC = m_pQuadTree->GetObjectCount();
}

void World::Update(float Dt)
{
	GetContext()->GetDebugRender()->Update(Dt);
	size_t ObjC = m_pQuadTree->GetObjectCount();
	++m_TickCounter;

	float ScrollSpeed = 200.0f;
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

	if (MoveDisp.x != 0.0f)
	{
		HitInfo swh;
		m_pQuadTree->SweepShapeClosest(*m_pPlayer->GetCollisionShape(), m_pPlayer->GetWorldTransform(), sf::Vector2f(MoveDisp.x, 0.0f), 1.1f, eCollisionGroup::Monster | eCollisionGroup::Static, swh);

		if (swh.m_Object)
		{
			MoveDisp.x = 0.0f;
		}
	}

	if (MoveDisp.y != 0.0f)
	{
		HitInfo swh;
		m_pQuadTree->SweepShapeClosest(*m_pPlayer->GetCollisionShape(), m_pPlayer->GetWorldTransform(), sf::Vector2f(0.0f, MoveDisp.y), 1.1f, eCollisionGroup::Monster | eCollisionGroup::Static, swh);

		if (swh.m_Object)
		{
			MoveDisp.y = 0.0f;
		}
	}

	m_pPlayer->Move(MoveDisp);

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

	HitInfo tr;
	m_pQuadTree->RayTraceClosest(Ray(m_pPlayer->GetWorldPosition(), Delta), eCollisionGroup::Monster | eCollisionGroup::Static, tr);

	if(tr.m_Object)
	{
		sf::Vector2f hitp = m_pPlayer->GetWorldPosition() + Delta * tr.m_Param;
		GetContext()->GetDebugRender()->AddCircle(hitp, 10.0f, 0.01f);
	}

	m_pPlayer->SetLocalRotation(atan2f(Delta.y, Delta.x) * 180.0f / 3.14159265358979323846f + 45.0f);

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
	GetQuadTree()->GetObjects(ViewBox, sf::Transform::Identity, eCollisionGroup::All, m_InViewObjects);

	std::sort(m_InViewObjects.begin(), m_InViewObjects.end(), 
		[](const HitInfo& Hit1, const HitInfo& Hit2)->bool
		{
			return Hit1.m_Object->GetWorldLayer() < Hit2.m_Object->GetWorldLayer();
		}
		);

	for (size_t Idx = 0; Idx < m_InViewObjects.size(); ++Idx)
	{
		Window->draw(*m_InViewObjects[Idx].m_Object);
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

bool World::IsObjectInView(SceneNode* pSceneNode)const
{
	for (size_t Idx = 0; Idx < m_InViewObjects.size(); ++Idx)
	{
		if (m_InViewObjects[Idx].m_Object == pSceneNode)
		{
			return true;
		}
	}

	return false;
}

}