#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/collision/aligned_box_shape.h>
#include <Survive/math_utils.h>

namespace Survive
{

SURVIVE_REG_TYPE(ConvexPolygonShape, SURVIVE_TYPELIST_1(CollisionShape))

Type* ConvexPolygonShape::GetType()const
{
	return TypeImpl<ConvexPolygonShape>::Instance();
}

bool ConvexPolygonShape::Contains(const sf::Vector2f& Point)const
{
	float Dp = 1.0f;

	for (size_t Idx0 = 0, Idx1 = GetPointC() - 1; Idx0 < GetPointC(); Idx1 = Idx0, ++Idx0) 
	{
		sf::Vector2f Edge = m_Points[Idx0] - m_Points[Idx1];
		sf::Vector2f D = MathUtils::GetVectorNormal(Edge);

		float Dp2 = MathUtils::DotProduct(D, Point);

		if (Dp * Dp2 < 0.0f)
			return false;
	}

	return true;
}

bool ConvexPolygonShape::Contains(const sf::Vector2f& Point, const sf::Transform& Tf)const
{
	ConvexPolygonShape Temp(*this);
	Temp.TransformShape(Tf);
	return Temp.Contains(Point);
}

void ConvexPolygonShape::GetAlignedHull(AlignedBoxShape* pHull)const
{
	pHull->SetCornerPosition(m_Points[0]);

	for (size_t Idx = 0; Idx < GetPointC(); ++Idx)
	{
		pHull->Extend(m_Points[Idx]);
	}
}

eCollisionShapeKind::Val ConvexPolygonShape::GetShapeKind()const
{
	return eCollisionShapeKind::ConvexPolygon;
}

void ConvexPolygonShape::TransformShape(const sf::Transform& Tf)
{
	if (!MathUtils::IsIdentity(Tf))
	{
		for (size_t Idx = 0; Idx < GetPointC(); ++Idx)
		{
			Tf.transformPoint(m_Points[Idx]);
		}
	}
}

sf::Vector2f ConvexPolygonShape::GetShapeCenter()const
{
	sf::Vector2f Result;

	for (size_t Idx = 0; Idx < GetPointC(); ++Idx)
	{
		Result += m_Points[Idx];
	}

	Result /= (float)GetPointC();

	return Result;
}

}