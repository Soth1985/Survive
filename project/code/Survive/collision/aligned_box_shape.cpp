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

}