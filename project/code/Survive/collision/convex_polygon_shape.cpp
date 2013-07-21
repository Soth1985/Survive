#include <Survive/collision/convex_polygon_shape.h>

namespace Survive
{

SURVIVE_REG_TYPE(ConvexPolygonShape, SURVIVE_TYPELIST_1(CollisionShape))

Type* ConvexPolygonShape::GetType()const
{
	return TypeImpl<ConvexPolygonShape>::Instance();
}

AlignedBoxShape ConvexPolygonShape::GetAlignedHull()const
{
	AlignedBoxShape Result;

	for (size_t Idx = 0; Idx < GetPointC(); ++Idx)
	{
		Result.Extend(m_Points[Idx]);
	}

	return Result;
}

}