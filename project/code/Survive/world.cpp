#include <Survive/world.h>
#include <Survive/math_utils.h>
#include <Survive/debug_render.h>
#include <Survive/content_manager.h>
#include <Survive/scene_nodes/scene_node.h>
#include <Survive/scene_nodes/landscape_node.h>
#include <Survive/scene_nodes/player_entity_node.h>
#include <Survive/scene_nodes/monster_entity_node.h>
#include <Survive/scene_nodes/respawn_node.h>

#include <Survive/collision/ray.h>
#include <Survive/templates/template_manager.h>
#include <Survive/templates/player_template.h>
#include <Survive/templates/monster_template.h>
#include <Survive/templates/respawn_template.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window.hpp>

#include <math.h>

namespace Survive
{

World::World(Context* pContext)
	:
m_pSceneRoot(new SceneNode()),
m_pContext(pContext),
m_pPlayer(0)
{
	m_View = m_pContext->GetRenderWindow()->getDefaultView();
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

	m_pContext->GetContentManager()->LoadTexture(eTextureID::ChaosLordBody);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::ChaosLordWeaponBolter);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::ChaosLordWeaponPlasma);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBadrukkBody);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkThrakaBody);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyChoppaBody1);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyChoppaBody2);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyChoppaBody3);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyChoppaBody4);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyShootaBody1);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyShootaBody2);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyShootaBody3);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkBoyShootaBody4);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkWarbossBody);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::OrkWarbossWeaponShoota);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::ProjectileBullet);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::ProjectilePlasma);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash1);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash2);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash3);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash4);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash4);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash5);
	m_pContext->GetContentManager()->LoadTexture(eTextureID::BloodSplash6);

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

	MonsterEntityNode* pMonster = CreateNode<MonsterEntityNode>(GetLayerRoot(eWorldLayer::GroundLayer));
	MonsterTemplate* pMonsterTmpl = TemplateManager::Instance().GetTemplate<MonsterTemplate>("OrkBoyChoppa");
	pMonster->InitFromTemplate(pMonsterTmpl);
	pMonster->SetLocalPosition(sf::Vector2f(100.0f, 200.0f));

	RespawnNode* pRespawn = CreateNode<RespawnNode>(GetLayerRoot(eWorldLayer::GroundLayer));
	RespawnTemplate* pRespawnTmpl = TemplateManager::Instance().GetTemplate<RespawnTemplate>("MonsterRespawn");
	pRespawn->InitFromTemplate(pRespawnTmpl);
	pRespawn->SetLocalPosition(sf::Vector2f(300.0f, 300.0f));
}

void World::Update(float Dt)
{
	GetContext()->GetDebugRender()->Update(Dt);

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

	HitInfo swh;
	m_pQuadTree->SweepShapeClosest(*m_pPlayer->GetCollisionShape(), m_pPlayer->GetWorldTransform(), MoveDisp, 1.0f, eCollisionGroup::Monster, swh);

	if(swh.m_Object)
	{
		MoveDisp *= 0.0f;
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
	m_pQuadTree->RayTraceClosest(Ray(m_pPlayer->GetWorldPosition(), Delta), eCollisionGroup::Monster, tr);

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
	Window->draw(*m_pSceneRoot);
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

}