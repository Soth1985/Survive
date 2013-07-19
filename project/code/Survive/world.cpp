#include <Survive/world.h>
#include <Survive/scene_nodes/scene_node.h>
#include <Survive/content_manager.h>
#include <Survive/scene_nodes/landscape_node.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window.hpp>

namespace Survive
{

World::World(Context* pContext)
	:
m_pSceneRoot(new SceneNode()),
m_pContext(pContext)
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

	const BigTexture* LandscapeTex = m_pContext->GetContentManager()->LoadBigTexture(eBigTextureID::Landscape);

	m_WorldSize.top = 0.0f;
	m_WorldSize.left = 0.0f;
	sf::Vector2u texSize = LandscapeTex->GetSize();
	m_WorldSize.height = texSize.y;
	m_WorldSize.width = texSize.x;
	LandscapeNode* Landscape = CreateNode<LandscapeNode>(GetLayerRoot(eWorldLayer::LandscapeLayer));
	Landscape->SetTexture(LandscapeTex);
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
	Window->setView(m_View);
	Window->draw(*m_pSceneRoot);
}

}