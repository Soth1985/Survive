#include <Survive/collision/collision_shape.h>

namespace Survive
{

SURVIVE_REG_TYPE(CollisionShape, SURVIVE_TYPELIST_1(Rtti))

CollisionShape::CollisionShape()
	:
m_CollisionGroup(eCollisionGroup::All)
{

}

Type* CollisionShape::GetType()const
{
	return TypeImpl<CollisionShape>::Instance();
}

}