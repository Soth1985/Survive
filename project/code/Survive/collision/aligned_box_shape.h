#pragma once

#include <Survive/forward.h>
#include <Survive/collision/collision_shape.h>
#include <Survive/collision/line_segment.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::AlignedBoxShape);

class AlignedBoxShape: public CollisionShape
{
public:

	virtual Type* GetType()const;

	AlignedBoxShape()
	{

	}

	AlignedBoxShape(const sf::Vector2f& CornerPosition, const sf::Vector2f& Size)
		:
	m_CornerPosition(CornerPosition),
	m_Size(Size)
	{

	}

	const sf::Vector2f& GetCornerPosition()const
	{
		return m_CornerPosition;
	}

	void SetCornerPosition(const sf::Vector2f& CornerPosition)
	{
		m_CornerPosition = CornerPosition;
	}

	const sf::Vector2f& GetSize()const
	{
		return m_Size;
	}

	void SetSize(const sf::Vector2f& Size)
	{
		m_Size = Size;
	}

	sf::Vector2f GetCenter()const
	{
		return m_CornerPosition + m_Size * 0.5f;
	}

	void Extend(const sf::Vector2f& Point);

	void Extend(const AlignedBoxShape& Box);

	bool Contains(const AlignedBoxShape& Box)const;

	bool Contains(const AlignedBoxShape& Box, const sf::Transform& BoxTf)const;

	void ToConvex(ConvexPolygonShape* pPoly)const;

	virtual bool Contains(const sf::Vector2f& Point)const;

	virtual bool Contains(const sf::Vector2f& Point, const sf::Transform& Tf)const;

	virtual void GetAlignedHull(AlignedBoxShape* pHull)const;

	virtual eCollisionShapeKind::Val GetShapeKind()const;

	virtual void TransformShape(const sf::Transform& Tf);

	virtual sf::Vector2f GetShapeCenter()const;

	sf::Vector2f GetCorner(int CornerIdx)const;

	LineSegment GetEdge(int EdgeIdx)const;

private:

	sf::Vector2f m_CornerPosition;
	sf::Vector2f m_Size;
};

}