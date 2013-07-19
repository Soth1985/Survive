#pragma once

#include <Survive/forward.h>
#include <Survive/context.h>
#include <Survive/type_info.h>

#include <SFML/Graphics/View.hpp>

namespace Survive
{

class World
{
public:

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

	SceneNode* GetLayerRoot(eWorldLayer::Val Layer)
	{
		return m_pLayers[Layer];
	}

	template <class T>
	T* CreateNode(SceneNode* pParent)
	{
		Type* NodeType = TypeImpl<T>::Instance();
		Type* SceneNodeType = TypeImpl<SceneNode>::Instance();

		if (IsConvertible(NodeType, SceneNodeType))
		{
			T* Result = new T();
			Result->m_pWorld = this;

			if (pParent)
			{
				pParent->AddChild(Result);
			}

			m_TypeNodeCache[NodeType].push_back(Result);

			return Result;
		}
		else
		{
			assert(0 && "Not a scene node");
			return 0;
		}
	}

private:

	typedef std::vector<SceneNode*> NodeList;
	typedef std::unordered_map<Type*, NodeList> TypeNodeCache;

	sf::View m_View;
	sf::FloatRect m_WorldSize;
	SceneNodePtr m_pSceneRoot;
	TypeNodeCache m_TypeNodeCache;
	std::array<SceneNode*, eWorldLayer::LayerCount> m_pLayers;
	Context* m_pContext;
};

}