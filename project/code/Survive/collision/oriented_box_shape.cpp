#include <Survive/collision/oriented_box_shape.h>
#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/math_utils.h>

namespace Survive
{

SURVIVE_REG_TYPE(OrientedBoxShape, SURVIVE_TYPELIST_1(CollisionShape))

Type* OrientedBoxShape::GetType()const
{
	return TypeImpl<OrientedBoxShape>::Instance();
}

bool OrientedBoxShape::Contains(const sf::Vector2f& Point)const
{
	AlignedBoxShape AlignedB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(GetHalfExtents().x * 2.0f, GetHalfExtents().y * 2.0f));

	sf::Vector2f RotatedPoint = Point - GetCenter();
	RotatedPoint = MathUtils::RotateVector(RotatedPoint, - GetRotation());
	RotatedPoint = RotatedPoint + GetHalfExtents();

	return AlignedB.Contains(RotatedPoint);
}

bool OrientedBoxShape::Contains(const sf::Vector2f& Point, const sf::Transform& Tf)const
{
	OrientedBoxShape Temp(*this);
	Temp.TransformShape(Tf);
	return Temp.Contains(Point);
}

sf::Vector2f OrientedBoxShape::GetCorner(int CornerIdx)const
{
	sf::Vector2f Corner = m_HalfExtents;

	switch(CornerIdx % 4) 
	{
	case 0:
		Corner.x = -Corner.x;
		break;
	case 1:
		break;
	case 2:
		Corner.y = -Corner.y;
		break;
	default:
		Corner = -Corner;
		break;
	}

	Corner = MathUtils::RotateVector(Corner, m_Rotation);
	return Corner + m_Center;
}

void OrientedBoxShape::GetAlignedHull(AlignedBoxShape* pHull)const
{
	AlignedBoxShape Result(m_Center, sf::Vector2f(0, 0));

	pHull->SetCornerPosition(m_Center);
	pHull->SetSize(sf::Vector2f(0.0f, 0.0f));

	sf::Vector2f Corner;

	for(int CornerIdx = 0; CornerIdx < 4; ++CornerIdx)
	{
		Corner = GetCorner(CornerIdx);
		pHull->Extend(Corner);
	}
}

LineSegment OrientedBoxShape::GetEdge(int EdgeIdx)const
{
	sf::Vector2f P1 = GetHalfExtents();
	sf::Vector2f P2 = GetHalfExtents();

	switch(EdgeIdx % 4) 
	{
	case 0:/* top edge */
		P1.x = -P1.x;
		break;
	case 1:/* right edge */
		P2.y = -P2.y;
		break;
	case 2:/* bottom edge */
		P1.y = -P1.y;
		P2 = -P2;
		break;
	default:/* left edge */
		P1 = -P1;
		P2.x = -P2.x;
		break;
	}

	P1 = MathUtils::RotateVector(P1, GetRotation());
	P1 = P1 + GetCenter();

	P2 = MathUtils::RotateVector(P1, GetRotation());
	P2 = P2 + GetCenter();

	return LineSegment(P1, P2);
}

void OrientedBoxShape::ToConvex(ConvexPolygonShape* pPoly)const
{
	pPoly->SetPointC(4);
	(*pPoly)[0] = GetCorner(0);
	(*pPoly)[1] = GetCorner(1);
	(*pPoly)[2] = GetCorner(2);
	(*pPoly)[3] = GetCorner(3);
}

eCollisionShapeKind::Val OrientedBoxShape::GetShapeKind()const
{
	return eCollisionShapeKind::OrientedBox;
}

void OrientedBoxShape::TransformShape(const sf::Transform& Tf)
{
	if (!MathUtils::IsIdentity(Tf))
	{
		sf::Vector2f Translate = MathUtils::GetTranslation(Tf);
		m_Center += Translate;

		//sf::Vector2f Scale = MathUtils::GetScale(Tf);

		//m_HalfExtents.x *= Scale.x;
		//m_HalfExtents.y *= Scale.y;

		m_Rotation += MathUtils::GetRotation(Tf);
	}
}

sf::Vector2f OrientedBoxShape::GetShapeCenter()const
{
	return m_Center;
}

}