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

			Result->m_UpdatePhase = RequestUpdatePhase(m_TypePhases[NodeType], Result->GetUpdateFrequency(), 30);

			/*if (Result->GetCollisionShape())
			{
				m_pQuadTree->AddObject(Result);
			}*/

			return Result;
		}
		else
		{
			assert(0 && "Not a scene node");
			return 0;
		}
	}

	template <class T>
	size_t GetNodeCount()
	{
		TypeNodeCache::iterator It = m_TypeNodeCache.find(TypeImpl<T>::Instance());

		if (It != m_TypeNodeCache.end())
			return It->second.size();
		else 
			return 0;
	}

	QuadTreeNode* GetQuadTree()
	{
		return m_pQuadTree.get();
	}

	unsigned int GetTickCounter()const
	{
		return m_TickCounter;
	}

	sf::Vector2f ConstrainToWorld(const sf::Vector2f& Center, const sf::Vector2f& HalfSize);

private:

	typedef std::vector<SceneNode*> NodeList;
	typedef std::unordered_map<Type*, NodeList> TypeNodeCache;
	typedef std::map<unsigned int, unsigned int> PhaseMap;
	typedef std::unordered_map<Type*, PhaseMap> TypePhasesMap;

	int RequestUpdatePhase(PhaseMap& PhasesMap, unsigned int Frequency, unsigned int MaxPhase);

	sf::View m_View;
	AlignedBoxShape m_WorldBound;
	SceneNodePtr m_pSceneRoot;
	QuadTreeNodePtr m_pQuadTree;
	PlayerEntityNode* m_pPlayer;
	TypeNodeCache m_TypeNodeCache;
	TypePhasesMap m_TypePhases;
	std::array<SceneNode*, eWorldLayer::LayerCount> m_pLayers;
	Context* m_pContext;
	unsigned int m_TickCounter;
};

}