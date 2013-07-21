#pragma once

#include <Survive/forward.h>
#include <Survive/collision/collision_shape.h>
#include <Survive/collision/aligned_box_shape.h>

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
		return m_Points[Idx];
	}

	const sf::Vector2f& operator[](size_t Idx)const
	{
		return m_Points[Idx];
	}

	AlignedBoxShape GetAlignedHull()const;

	int GetMaxPointC()const
	{
		return MaxPointC;
	}

private:

	static const int MaxPointC = 15;

	std::array<sf::Vector2f, MaxPointC> m_Points;
	int m_PointC;
	//std::vector<sf::Vector2f> m_Points;
};

}