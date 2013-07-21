#include <Survive/collision/aligned_box_shape.h>

namespace Survive
{

SURVIVE_REG_TYPE(AlignedBoxShape, SURVIVE_TYPELIST_1(CollisionShape))

Type* AlignedBoxShape::GetType()const
{
	return TypeImpl<AlignedBoxShape>::Instance();
}

void AlignedBoxShape::Extend(const sf::Vector2f& Point)
{
	AlignedBoxShape Result;
	sf::Vector2f NewPosition;
	sf::Vector2f NewSize;
	NewPosition.x = std::min(m_CornerPosition.x, Point.x);
	NewPosition.y = std::min(m_CornerPosition.y, Point.y);
	NewSize.x = std::max(m_CornerPosition.x + m_Size.x, Point.x);
	NewSize.y = std::max(m_CornerPosition.y + m_Size.y, Point.y);
	NewSize = NewSize - NewPosition;
	m_CornerPosition = NewPosition;
	m_Size = NewSize;
}

void AlignedBoxShape::Extend(const AlignedBoxShape& Box)
{
	sf::Vector2f MaxCorner = Box.GetCornerPosition() + Box.GetSize();
	Extend(MaxCorner);
}

bool AlignedBoxShape::Contains(const sf::Vector2f& Point)const
{
	float Left = m_CornerPosition.x;
	float Right = Left + m_Size.x;
	float Bottom = m_CornerPosition.y;
	float Top = Bottom + m_Size.y;
	return Left <= Point.x && Bottom <= Point.y && Point.x <= Right && Point.y <= Top;
}

sf::Vector2f AlignedBoxShape::GetCorner(int CornerIdx)const
{
	sf::Vector2f Corner = GetCornerPosition();

	switch(CornerIdx % 4)
	{
	case 0:
		Corner.x += GetSize().x;
		break;
	case 1:
		Corner = Corner + GetSize();
		break;
	case 2:
		Corner.y += GetSize().y;
		break;
	default:
		break;
	}

	return Corner;
}

LineSegment AlignedBoxShape::GetEdge(int EdgeIdx)const
{
	sf::Vector2f P1 = GetCornerPosition();
	sf::Vector2f P2 = GetCornerPosition();

	switch(EdgeIdx % 4) 
	{
	case 0:/* top edge */
		P1.y += GetSize().y;
		P2 += GetSize();
		break;
	case 1:/* right edge */
		P1 += GetSize();
		P2.x += GetSize().x;
		break;
	case 2:/* bottom edge */
		P1.x += GetSize().x;
		break;
	default:/* left edge */
		P2.y += GetSize().y;
		break;
	}

	return LineSegment(P1, P2);
}

}