#include <Survive/collision/oriented_box_shape.h>
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

AlignedBoxShape OrientedBoxShape::GetAlignedHull()const
{
	AlignedBoxShape Result(m_Center, sf::Vector2f(0, 0));

	sf::Vector2f Corner;

	for(int CornerIdx = 0; CornerIdx < 4; ++CornerIdx)
	{
		Corner = GetCorner(CornerIdx);
		Result.Extend(Corner);
	}

	return Result;
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

}