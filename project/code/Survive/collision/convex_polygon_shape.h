#pragma once

#include <Survive/forward.h>
#include <Survive/collision/collision_shape.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::ConvexPolygonShape);

class ConvexPolygonShape: public CollisionShape
{
public:

	virtual Type* GetType()const;

	ConvexPolygonShape()
	{

	}

	ConvexPolygonShape(size_t PointC)
		:
	m_PointC(PointC)
	{
		//m_Points.resize(PointC);
	}

	size_t GetPointC()const
	{
		//return m_Points.size();
		return m_PointC;
	}

	void SetPointC(size_t PointC)
	{
		//m_Points.resize(PointC);

		assert(PointC < MaxPointC);
		m_PointC = PointC;
	}

	sf::Vector2f& operator[](size_t Idx)
	{
		assert(Idx < m_PointC);
		return m_Points[Idx];
	}

	const sf::Vector2f& operator[](size_t Idx)const
	{
		assert(Idx < m_PointC);
		return m_Points[Idx];
	}

	virtual bool Contains(const sf::Vector2f& Point)const;

	virtual bool Contains(const sf::Vector2f& Point, const sf::Transform& Tf)const;

	virtual void GetAlignedHull(AlignedBoxShape* pHull)const;

	virtual eCollisionShapeKind::Val GetShapeKind()const;

	virtual void TransformShape(const sf::Transform& Tf);

	virtual sf::Vector2f GetShapeCenter()const;

	int GetMaxPointC()const
	{
		return MaxPointC;
	}

private:

	static const int MaxPointC = 15;

	std::array<sf::Vector2f, MaxPointC> m_Points;
	size_t m_PointC;
	//std::vector<sf::Vector2f> m_Points;
};

}