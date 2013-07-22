#include <Survive/quad_tree_node.h>
#include <Survive/scene_nodes/scene_node.h>
#include <Survive/collision/intersection_tests.h>
#include <Survive/collision/sweep_tests.h>

namespace Survive
{

QuadTreeNode::QuadTreeNode(const AlignedBoxShape& Bounds, QuadTreeNode* Parent, char Level, char Id)
	:
m_Bounds(Bounds),
m_pParent(Parent),
m_Level(Level),
m_Id(Id)
{

}

void QuadTreeNode::GetNodesIntersectingAlignedBox(const AlignedBoxShape& Box, const sf::Transform& BoxTf, NodeList& Nodes)
{
	if (IntersectionTests::HasIntersectionAlignedBoxAlignedBox(Box, BoxTf, m_Bounds, sf::Transform::Identity))
	{
		Nodes.push_back(this);
	}

	for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
	{
		m_pChildren[Idx]->GetNodesIntersectingAlignedBox(Box, BoxTf, Nodes);
	}
}

void QuadTreeNode::GetObjects(const sf::Vector2f& Pos, HitList& Objects)
{
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{
		SceneNode* pObject = *It;
		if (pObject->GetCollisionShape()->Contains(Pos, pObject->GetWorldTransform()))
		{
			Objects.push_back(HitInfo(*It));
		}
	}

	if(m_pChildren[0])
	{
		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (m_pChildren[Idx]->GetBounds().Contains(Pos))
			{
				m_pChildren[Idx]->GetObjects(Pos, Objects);
			}
		}
	}
}

void QuadTreeNode::GetObjects(const CollisionShape& Shape, const sf::Transform& ShapeTf, HitList& Objects)
{
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{
		SceneNode* pObject = *It;
		if (IntersectionTests::HasIntersectionShapeShape(*pObject->GetCollisionShape(), pObject->GetWorldTransform(), Shape, ShapeTf))
		{
			Objects.push_back(HitInfo(pObject));
		}
	}

	if(m_pChildren[0])
	{
		AlignedBoxShape Temp;
		Shape.GetAlignedHull(&Temp);

		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (IntersectionTests::HasIntersectionAlignedBoxAlignedBox(Temp, ShapeTf, m_pChildren[Idx]->GetBounds(), sf::Transform::Identity))
			{
				m_pChildren[Idx]->GetObjects(Shape, ShapeTf, Objects);
			}
		}
	}
}

void QuadTreeNode::RayTrace(const Ray& R, HitList& Objects)
{
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{ 
		float Param = 0.0f;
		SceneNode* pObject = *It;

		if (IntersectionTests::FindIntersectionRayShape(R, *pObject->GetCollisionShape(), pObject->GetWorldTransform(), false, Param) == 1)
		{
			Objects.push_back(HitInfo(pObject, Param));
		}
	}

	if(m_pChildren[0])
	{
		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (IntersectionTests::HasIntersectionRayAlignedBox(R, m_pChildren[Idx]->GetBounds(), sf::Transform::Identity))
			{
				m_pChildren[Idx]->RayTrace(R, Objects);
			}
		}
	}
}

void QuadTreeNode::RayTraceClosest(const Ray& R, HitInfo& Result)
{
	if (!m_pParent)
		Result.m_Param = FLT_MAX;

	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{ 
		float Param = FLT_MAX;
		SceneNode* pObject = *It;

		if (IntersectionTests::FindIntersectionRayShape(R, *pObject->GetCollisionShape(), pObject->GetWorldTransform(), true, Param) == 1)
		{
			if (Param < Result.m_Param)
			{
				Result.m_Object = pObject;
				Result.m_Param = Param;
			}
		}
	}

	if(m_pChildren[0])
	{
		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (IntersectionTests::HasIntersectionRayAlignedBox(R, m_pChildren[Idx]->GetBounds(), sf::Transform::Identity))
			{
				m_pChildren[Idx]->RayTraceClosest(R, Result);
			}
		}
	}
}

void QuadTreeNode::SweepShapeClosest(const CollisionShape& Shape, const sf::Transform& ShapeTf, const sf::Vector2f& V, float Tmax, HitInfo& Result)
{
	if (!m_pParent)
		Result.m_Param = FLT_MAX;

	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{ 
		float Tfirst = FLT_MAX;
		float Tlast = FLT_MAX;
		SceneNode* pObject = *It;

		if (SweepTests::SweepShapeShape(Shape, ShapeTf, *pObject->GetCollisionShape(), pObject->GetWorldTransform(), V, pObject->GetVelocity(), Tmax, Tfirst, Tlast) == 1)
		{
			if (Tfirst < Result.m_Param)
			{
				Result.m_Object = pObject;
				Result.m_Param = Tfirst;
			}
		}
	}

	AlignedBoxShape ShapeTrace;
	Shape.GetAlignedHull(&ShapeTrace);
	ShapeTrace.TransformShape(ShapeTf);
	ShapeTrace.Extend(ShapeTrace.GetCenter() + V * Tmax + ShapeTrace.GetSize());

	if(m_pChildren[0])
	{
		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (IntersectionTests::HasIntersectionAlignedBoxAlignedBox(ShapeTrace, sf::Transform::Identity, m_pChildren[Idx]->GetBounds(), sf::Transform::Identity))
			{
				m_pChildren[Idx]->SweepShapeClosest(Shape, ShapeTf, V, Tmax, Result);
			}
		}
	}

}

void QuadTreeNode::AddObject(SceneNode* pObject)
{
	AlignedBoxShape Temp;
	pObject->GetCollisionShape()->GetAlignedHull(&Temp);
	Temp.TransformShape(pObject->GetWorldTransform());

	if (m_pChildren[0])
	{
		for(size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (m_pChildren[Idx]->GetBounds().Contains(Temp))
			{
				m_pChildren[Idx]->AddObject(pObject);
				return;
			}
		}
	}
	else if (m_Bounds.Contains(Temp))
	{
		if (m_pObjects.size() + 1 <= CapacityToSplit || m_Level > MaxDepth)
		{
			m_pObjects.insert(pObject);
			pObject->m_pQuadTreeNode = this;
			return;
		}
		else
		{
			m_pObjects.insert(pObject);
			pObject->m_pQuadTreeNode = this;

			CreateChildren();
			MoveObjects();
		}
	}
	else if (m_pParent == 0)
	{
		m_pObjects.insert(pObject);
		pObject->m_pQuadTreeNode = this;
	}
}

bool QuadTreeNode::Remove(SceneNode* pObject)
{
	if (m_pObjects.erase(pObject) != 0)
	{
		return true;
	}
	else
	{
		if (m_pChildren[0])
		{
			AlignedBoxShape Temp;
			sf::Transform ObjTf = pObject->GetWorldTransform();
			pObject->GetCollisionShape()->GetAlignedHull(&Temp);
			Temp.TransformShape(ObjTf);

			for(size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
			{
				if (m_pChildren[Idx]->GetBounds().Contains(Temp))
				{
					if (m_pChildren[Idx]->Remove(pObject))
						return true;
				}
			}
		}
	}

	return false;
}

void QuadTreeNode::Update(SceneNode* pObject)
{
	AlignedBoxShape Temp;
	pObject->GetCollisionShape()->GetAlignedHull(&Temp);
	sf::Transform ObjTf = pObject->GetWorldTransform();
	Temp.TransformShape(ObjTf);

	if (m_Bounds.Contains(Temp))
	{
		return;
	}
	else
	{
		QuadTreeNode* pParent = m_pParent;
		QuadTreeNode* pPrevParent = 0;

		while (pParent)
		{
			if (pParent->GetBounds().Contains(Temp))
			{
				pParent->AddObject(pObject);
				return;
			}

			pPrevParent = pParent;
			pParent = const_cast<QuadTreeNode*>(pParent->GetParent());
		}

		if(pPrevParent)
			pPrevParent->AddObject(pObject);
	}
}

void QuadTreeNode::CreateChildren()
{
	AlignedBoxShape Temp;

	sf::Vector2f Offset;
	sf::Vector2f Step = m_Bounds.GetSize() * 0.5f;

	for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
	{
		Offset.x = ((Idx & 1) ? Step.x : -Step.x);
		Offset.y = ((Idx & 2) ? Step.y : -Step.y);

		sf::Vector2f Position = m_Bounds.GetCornerPosition() + Offset;

		m_pChildren[Idx].reset(new QuadTreeNode(AlignedBoxShape(Position, Step), this, m_Level + 1, Idx));
	}
}

void QuadTreeNode::MoveObjects()
{
	AlignedBoxShape Temp;
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{
		SceneNode* pObject = *It;
		pObject->GetCollisionShape()->GetAlignedHull(&Temp);

		for(size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (m_pChildren[Idx]->GetBounds().Contains(Temp, pObject->GetWorldTransform()))
			{
				m_pChildren[Idx]->AddObject(pObject);
				pObject->m_pQuadTreeNode = m_pChildren[Idx].get();
				m_pObjects.erase(It);
			}
		}
	}
}

}