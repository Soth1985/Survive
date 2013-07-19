#pragma once

#include <Survive/forward.h>
#include <Survive/context.h>

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

	World(Context* pContext);

	~World();

	void Init();

	void Update(float Dt);

	void Draw(sf::RenderWindow* Window);

	Context* GetContext()
	{
		return m_pContext;
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
	Context* m_pContext;
};

}