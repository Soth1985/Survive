#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/math_utils.h>

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

void AlignedBoxShape::GetAlignedHull(AlignedBoxShape* pHull)const
{
	*pHull = *this;
}

bool AlignedBoxShape::Contains(const AlignedBoxShape& Box)const
{
	return Contains(Box.GetCorner(1)) && Contains(Box.GetCorner(3));
}

bool AlignedBoxShape::Contains(const AlignedBoxShape& Box, const sf::Transform& BoxTf)const
{
	AlignedBoxShape Temp(Box);
	Temp.TransformShape(BoxTf);
	return Contains(Temp);
}

bool AlignedBoxShape::Contains(const sf::Vector2f& Point, const sf::Transform& Tf)const
{
	AlignedBoxShape Temp(*this);
	Temp.TransformShape(Tf);
	return Temp.Contains(Point);
}

void AlignedBoxShape::ToConvex(ConvexPolygonShape* pPoly)const
{
	pPoly->SetPointC(4);
	(*pPoly)[0] = GetCorner(0);
	(*pPoly)[1] = GetCorner(1);
	(*pPoly)[2] = GetCorner(2);
	(*pPoly)[3] = GetCorner(3);
}

eCollisionShapeKind::Val AlignedBoxShape::GetShapeKind()const
{
	return eCollisionShapeKind::AlignedBox;
}

void AlignedBoxShape::TransformShape(const sf::Transform& Tf)
{
	if (!MathUtils::IsIdentity(Tf))
	{
		sf::Vector2f Translate = MathUtils::GetTranslation(Tf);
		m_CornerPosition += Translate;

		//sf::Vector2f Scale = MathUtils::GetScale(Tf);

		//m_Size.x *= Scale.x;
		//m_Size.y *= Scale.y;
	}
}

sf::Vector2f AlignedBoxShape::GetShapeCenter()const
{
	return m_CornerPosition + m_Size * 0.5f;
}

}