#pragma once

#include <Survive/forward.h>
#include <Survive/hit_info.h>
#include <Survive/collision/aligned_box_shape.h>

namespace Survive
{

class QuadTreeNode
{
public:

	typedef std::vector<HitInfo> HitList;
	typedef std::vector<QuadTreeNode*> NodeList;

	QuadTreeNode(const AlignedBoxShape& Bounds, QuadTreeNode* Parent, char Level, char Id);

	void GetNodesIntersectingAlignedBox(const AlignedBoxShape& Box, const sf::Transform& BoxTf, NodeList& Nodes);

	void GetObjects(const sf::Vector2f& Pos, HitList& Objects);

	void GetObjects(const CollisionShape& Shape, const sf::Transform& ShapeTf, HitList& Objects);

	void RayTrace(const Ray& R, HitList& Objects);

	void RayTraceClosest(const Ray& R, HitInfo& Result);

	void SweepShapeClosest(const CollisionShape& Shape, const sf::Transform& ShapeTf, const sf::Vector2f& V, float Tmax, HitInfo& Result);

	void AddObject(SceneNode* pObject);
	bool Remove(SceneNode* pObject);
	void Update(SceneNode* pObject);

	const AlignedBoxShape& GetBounds()const
	{
		return m_Bounds;
	}

	int GetLevel()const
	{
		return m_Level;
	}

	int GetID()const
	{
		return m_Id;
	}

	const QuadTreeNode* GetParent()const
	{
		return m_pParent;
	}
	
private:

	typedef std::unordered_set<SceneNode*> ObjectSet;

	void CreateChildren();
	void MoveObjects();

	static const int CapacityToSplit = 15;
	static const int MaxDepth = 5;

	AlignedBoxShape m_Bounds;
	QuadTreeNode* m_pParent;
	ObjectSet m_pObjects;
	std::array<QuadTreeNodePtr, 4> m_pChildren;
	char m_Level;
	char m_Id;
};

}