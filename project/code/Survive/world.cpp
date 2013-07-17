#include <Survive/world.h>
#include <Survive/scene_node.h>
#include <Survive/content_manager.h>
#include <Survive/landscape_node.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window.hpp>

namespace Survive
{

World::World()
	:
m_pSceneRoot(new SceneNode()),
m_pContentManager(new ContentManager())
{

}

World::~World()
{

}

void World::Init(const sf::View& View)
{
	m_View = View;

	for (size_t Idx = 0; Idx < m_pLayers.size(); ++Idx)
	{
		m_pLayers[Idx] = new SceneNode();

		m_pSceneRoot->AddChild(m_pLayers[Idx]);
	}

	const BigTexture* landscapeTex = m_pContentManager->BigTextures().Get(eBigTextureID::Landscape);
	m_WorldSize.top = 0.0f;
	m_WorldSize.left = 0.0f;
	sf::Vector2u texSize = landscapeTex->GetSize();
	m_WorldSize.height = texSize.y;
	m_WorldSize.width = texSize.x;
	m_pLayers[LandscapeLayer]->AddChild(new LandscapeNode(landscapeTex));
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

	m_View.move(MoveDisp);

	sf::Vector2f halfDim = m_View.getSize() * 0.5f;
	sf::Vector2f topLeft = m_View.getCenter() - halfDim;
	sf::Vector2f bottomRight = m_View.getCenter() + halfDim;	

	sf::Vector2f center = m_View.getCenter();

	if (topLeft.x < 0.0f)
	{
		center.x = halfDim.x;
	}
	else if (bottomRight.x > m_WorldSize.width)
	{
		center.x = m_WorldSize.width - halfDim.x;
	}

	if (topLeft.y < 0.0f)
	{
		center.y = halfDim.y;
	}
	else if (bottomRight.y > m_WorldSize.height)
	{
		center.y = m_WorldSize.height - halfDim.y;
	}

	m_View.setCenter(center);

	m_pSceneRoot->Update(Dt);
}

void World::Draw(sf::RenderWindow* Window)
{
	auto v = Window->getDefaultView();
	Window->setView(m_View);
	Window->draw(*m_pSceneRoot);
}

}