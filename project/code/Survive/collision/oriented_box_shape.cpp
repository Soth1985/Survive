#include <Survive/collision/oriented_box_shape.h>

namespace Survive
{

SURVIVE_REG_TYPE(OrientedBoxShape, SURVIVE_TYPELIST_1(CollisionShape))

Type* OrientedBoxShape::GetType()const
{
	return TypeImpl<OrientedBoxShape>::Instance();
}

}