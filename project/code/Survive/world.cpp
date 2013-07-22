#include <Survive/world.h>
#include <Survive/scene_nodes/scene_node.h>
#include <Survive/content_manager.h>
#include <Survive/scene_nodes/landscape_node.h>
#include <Survive/scene_nodes/player_entity_node.h>

#include <Survive/templates/template_manager.h>
#include <Survive/templates/player_template.h>

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
	const BigTexture* LandscapeTex = m_pContext->GetContentManager()->LoadBigTexture(eBigTextureID::Landscape);

	m_WorldSize.top = 0.0f;
	m_WorldSize.left = 0.0f;
	sf::Vector2u texSize = LandscapeTex->GetSize();
	m_WorldSize.height = texSize.y;
	m_WorldSize.width = texSize.x;
	LandscapeNode* Landscape = CreateNode<LandscapeNode>(GetLayerRoot(eWorldLayer::LandscapeLayer));
	Landscape->SetTexture(LandscapeTex);

	m_pPlayer = CreateNode<PlayerEntityNode>(GetLayerRoot(eWorldLayer::GroundLayer));

	PlayerTemplate* PlayerTmpl = TemplateManager::Instance().GetTemplate<PlayerTemplate>("Player");

	m_pPlayer->InitFromTemplate(PlayerTmpl);

	m_pPlayer->SetLocalPosition(sf::Vector2f(100.0f, 100.0f));
}

void World::Update(float Dt)
{
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

	m_pPlayer->Move(MoveDisp);

	sf::FloatRect PlayerBounds = m_pPlayer->GetBounds();
	sf::Vector2f PlayerHalfSize(PlayerBounds.width * 0.5f, PlayerBounds.height * 0.5f);
	m_pPlayer->SetLocalPosition(ConstrainToWorld(m_pPlayer->GetLocalPosition(), PlayerHalfSize));

	m_View.setCenter(m_pPlayer->GetWorldPosition());

	sf::Vector2i MousePos = sf::Mouse::getPosition(*GetContext()->GetRenderWindow());
	sf::Vector2f WorldPos = GetContext()->GetRenderWindow()->mapPixelToCoords(MousePos);
	sf::Vector2f Delta = WorldPos - m_pPlayer->GetLocalPosition();
	m_pPlayer->SetLocalRotation(atan2f(Delta.y, Delta.x) * 180.0f / 3.14159265358979323846f + 45.0f);

	m_View.setCenter(ConstrainToWorld(m_View.getCenter(), m_View.getSize() * 0.5f));

	m_pSceneRoot->Update(Dt);
}

void World::Draw(sf::RenderWindow* Window)
{
	Window->setView(m_View);
	Window->draw(*m_pSceneRoot);
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
	else if (BottomRight.x > m_WorldSize.width)
	{
		Result.x = m_WorldSize.width - HalfSize.x;
	}

	if (TopLeft.y < 0.0f)
	{
		Result.y = HalfSize.y;
	}
	else if (BottomRight.y > m_WorldSize.height)
	{
		Result.y = m_WorldSize.height - HalfSize.y;
	}

	return Result;
}

}