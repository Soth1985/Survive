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
	{
		m_Points.resize(PointC);
	}

	size_t GetPointC()const
	{
		return m_Points.size();
	}

	void SetPointC(size_t PointC)
	{
		m_Points.resize(PointC);
	}

	sf::Vector2f& operator[](size_t Idx)
	{
		return m_Points[Idx];
	}

	const sf::Vector2f& operator[](size_t Idx)const
	{
		return m_Points[Idx];
	}

private:

	std::vector<sf::Vector2f> m_Points;
};

}