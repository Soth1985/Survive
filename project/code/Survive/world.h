#pragma once

#include <Survive/forward.h>
#include <Survive/context.h>
#include <Survive/type_info.h>
#include <Survive/quad_tree_node.h>

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

	const AlignedBoxShape& GetWorldBound()const
	{
		return m_WorldBound;
	}

	SceneNode* GetLayerRoot(eWorldLayer::Val Layer)
	{
		return m_pLayers[Layer];
	}

	PlayerEntityNode* GetPlayer()
	{
		return m_pPlayer;
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

			if (Result->GetCollisionShape())
			{
				m_pQuadTree->AddObject(Result);
			}

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

	sf::Vector2f ConstrainToWorld(const sf::Vector2f& Center, const sf::Vector2f& HalfSize);

	sf::View m_View;
	AlignedBoxShape m_WorldBound;
	SceneNodePtr m_pSceneRoot;
	QuadTreeNodePtr m_pQuadTree;
	PlayerEntityNode* m_pPlayer;
	TypeNodeCache m_TypeNodeCache;
	std::array<SceneNode*, eWorldLayer::LayerCount> m_pLayers;
	Context* m_pContext;
};

}