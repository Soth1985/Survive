#include <Survive/scene_nodes/dynamic_entity_node.h>
#include <Survive/world.h>

namespace Survive
{

SURVIVE_REG_TYPE(DynamicEntityNode, SURVIVE_TYPELIST_1(SceneNode))

Type* DynamicEntityNode::GetType()const
{
	return TypeImpl<DynamicEntityNode>::Instance();
}

void DynamicEntityNode::DynamicMove(sf::Vector2f Disp, bool SweepBothDirections)
{
	unsigned int CollisionMask = eCollisionGroup::Monster | eCollisionGroup::Static | eCollisionGroup::Player;
	float SweepTmax = 1.5f;

	if (SweepBothDirections)
	{
		if (Disp.x != 0.0f)
		{
			HitInfo Hit;
			GetWorld()->GetQuadTree()->SweepShapeClosest(*GetCollisionShape(), GetWorldTransform(), sf::Vector2f(Disp.x, 0.0f), SweepTmax, CollisionMask, this, Hit);

			if (Hit.m_pObject)
			{
				Disp.x = 0.0f;
			}
		}

		if (Disp.y != 0.0f)
		{
			HitInfo Hit;
			GetWorld()->GetQuadTree()->SweepShapeClosest(*GetCollisionShape(), GetWorldTransform(), sf::Vector2f(0.0f, Disp.y), SweepTmax, CollisionMask, this, Hit);

			if (Hit.m_pObject)
			{
				Disp.y = 0.0f;
			}
		}
	}
	else
	{
		HitInfo Hit;
		GetWorld()->GetQuadTree()->SweepShapeClosest(*GetCollisionShape(), GetWorldTransform(), Disp, SweepTmax, CollisionMask, this, Hit);

		if (Hit.m_pObject)
		{
			Disp.x = 0.0f;
			Disp.y = 0.0f;
		}
	}

	Move(Disp);
}

}