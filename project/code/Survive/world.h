#pragma once

#include <Survive/forward.h>

#include <SFML/Graphics/View.hpp>

namespace Survive
{

class World
{
public:

	enum eLayer
	{
		LandscapeLayer,
		GroundLayer,
		GuiLayer,
		LayerCount
	};

	World();

	~World();

	void Init(const sf::View& View);

	void Update(float Dt);

	void Draw(sf::RenderWindow* Window);

	ContentManager* GetContentManager()
	{
		return m_pContentManager.get();
	}

	SceneNode* GetSceneRoot()
	{
		return m_pSceneRoot.get();
	}

	const sf::FloatRect& GetWorldSize()const
	{
		return m_WorldSize;
	}

private:

	sf::View m_View;
	sf::FloatRect m_WorldSize;
	SceneNodePtr m_pSceneRoot;
	std::array<SceneNode*, LayerCount> m_pLayers;
	ContentManagerPtr m_pContentManager;
};

}