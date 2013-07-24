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

void QuadTreeNode::GetObjects(const sf::Vector2f& Pos, unsigned int Mask, HitList& Objects)
{
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{
		SceneNode* pObject = *It;
		const CollisionShape* pShape = pObject->GetCollisionShape();
		if (pShape->CheckCollisionGroup(Mask) && pShape->Contains(Pos, pObject->GetWorldTransform()))
		{
			Objects.push_back(HitInfo(pObject));
		}
	}

	if(m_pChildren[0])
	{
		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (m_pChildren[Idx]->GetBounds().Contains(Pos))
			{
				m_pChildren[Idx]->GetObjects(Pos, Mask, Objects);
			}
		}
	}
}

void QuadTreeNode::GetObjects(const CollisionShape& Shape, const sf::Transform& ShapeTf, unsigned int Mask, HitList& Objects)
{
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{
		SceneNode* pObject = *It;
		const CollisionShape* pShape = pObject->GetCollisionShape();
		if (pShape->CheckCollisionGroup(Mask) && IntersectionTests::HasIntersectionShapeShape(*pShape, pObject->GetWorldTransform(), Shape, ShapeTf))
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
				m_pChildren[Idx]->GetObjects(Shape, ShapeTf, Mask, Objects);
			}
		}
	}
}

void QuadTreeNode::RayTrace(const Ray& R, unsigned int Mask, HitList& Objects)
{
	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{ 
		float Param = 0.0f;
		SceneNode* pObject = *It;
		const CollisionShape* pShape = pObject->GetCollisionShape();

		if (pShape->CheckCollisionGroup(Mask) && IntersectionTests::FindIntersectionRayShape(R, *pShape, pObject->GetWorldTransform(), false, Param) == 1)
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
				m_pChildren[Idx]->RayTrace(R, Mask, Objects);
			}
		}
	}
}

void QuadTreeNode::RayTraceClosest(const Ray& R, unsigned int Mask, HitInfo& Result)
{
	if (!m_pParent)
		Result.m_Param = FLT_MAX;

	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{ 
		float Param = FLT_MAX;
		SceneNode* pObject = *It;
		const CollisionShape* pShape = pObject->GetCollisionShape();

		if (pShape->CheckCollisionGroup(Mask) && IntersectionTests::FindIntersectionRayShape(R, *pShape, pObject->GetWorldTransform(), true, Param) == 1)
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
				m_pChildren[Idx]->RayTraceClosest(R, Mask, Result);
			}
		}
	}
}

void QuadTreeNode::SweepShapeClosest(const CollisionShape& Shape, const sf::Transform& ShapeTf, const sf::Vector2f& V, float Tmax, unsigned int Mask, HitInfo& Result)
{
	if (!m_pParent)
		Result.m_Param = FLT_MAX;

	for (ObjectSet::iterator It = m_pObjects.begin(); It != m_pObjects.end(); ++It)
	{ 
		float Tfirst = FLT_MAX;
		float Tlast = FLT_MAX;
		SceneNode* pObject = *It;
		const CollisionShape* pShape = pObject->GetCollisionShape();

		if (pShape->CheckCollisionGroup(Mask) && SweepTests::SweepShapeShape(Shape, ShapeTf, *pShape, pObject->GetWorldTransform(), V, pObject->GetVelocity(), Tmax, Tfirst, Tlast) == 1)
		{
			if (Tfirst < Result.m_Param && Tfirst < Tlast)
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
				m_pChildren[Idx]->SweepShapeClosest(Shape, ShapeTf, V, Tmax, Mask, Result);
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
	
	if (m_Bounds.Contains(Temp))
	{
		if (m_pObjects.size() + 1 <= CapacityToSplit || m_Level > MaxDepth)
		{
			m_pObjects.insert(pObject);
			pObject->SetQuadTreeNode(this);
			return;
		}
		else if (!m_pChildren[0])
		{
			m_pObjects.insert(pObject);
			pObject->SetQuadTreeNode(this);

			int oc = GetObjectCount();
			CreateChildren();
			MoveObjects();
			int oc1 = GetObjectCount();

			assert(oc==oc1);
			return;
		}
	}
	
	//if (m_pParent == 0)
	{
		m_pObjects.insert(pObject);
		pObject->SetQuadTreeNode(this);
	}
	//else
	//	__asm int 3;
}

bool QuadTreeNode::Remove(SceneNode* pObject)
{
	if (m_pObjects.erase(pObject) != 0)
	{
		pObject->SetQuadTreeNode(0);
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
		if (m_pParent)
			m_pObjects.erase(pObject);

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
		Offset.x = ((Idx & 1) ? Step.x : 0);
		Offset.y = ((Idx & 2) ? Step.y : 0);

		sf::Vector2f Position = m_Bounds.GetCornerPosition() + Offset;

		m_pChildren[Idx].reset(new QuadTreeNode(AlignedBoxShape(Position, Step), this, m_Level + 1, Idx));
	}
}

void QuadTreeNode::MoveObjects()
{
	AlignedBoxShape Temp;
	ObjectSet::iterator It = m_pObjects.begin();
	size_t oc = GetObjectCount();

	while (It != m_pObjects.end())
	{
		SceneNode* pObject = *It;
		bool Increment = true;
		pObject->GetCollisionShape()->GetAlignedHull(&Temp);

		for(size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			if (m_pChildren[Idx]->GetBounds().Contains(Temp, pObject->GetWorldTransform()))
			{
				m_pChildren[Idx]->AddObject(pObject);
				//pObject->SetQuadTreeNode(m_pChildren[Idx].get());
				It = m_pObjects.erase(It);
				Increment = false;
				assert(oc==GetObjectCount());
				break;
			}
		}

		if (Increment)
			++It;
	}
}

size_t QuadTreeNode::GetObjectCount()const
{
	size_t Result = m_pObjects.size();

	if (m_pChildren[0])
	{
		for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
		{
			Result += m_pChildren[Idx]->GetObjectCount();
		}
	}

	return Result;
}

}