#pragma once

#include <Survive/forward.h>
#include <Survive/collision/collision_shape.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::OrientedBoxShape);

class OrientedBoxShape: public CollisionShape
{
public:

	virtual Type* GetType()const;

	OrientedBoxShape()
		:
	m_Rotation(0.0f)
	{

	}

	OrientedBoxShape(const sf::Vector2f& Center, const sf::Vector2f& HalfExtents, float Rotation)
		:
	m_Center(Center),
	m_HalfExtents(HalfExtents),
	m_Rotation(Rotation)
	{

	}

	const sf::Vector2f& GetCenter()const
	{
		return m_Center;
	}

	void SetCenter(const sf::Vector2f& Center)
	{
		m_Center = Center;
	}

	const sf::Vector2f& GetHalfExtents()const
	{
		return m_HalfExtents;
	}

	void SetHalfExtents(const sf::Vector2f& HalfExtents)
	{
		m_HalfExtents = HalfExtents;
	}

	float GetRotation()const
	{
		return m_Rotation;
	}

	void SetRotation(float Rotation)
	{
		m_Rotation = Rotation;
	}

private:

	sf::Vector2f m_Center;
	sf::Vector2f m_HalfExtents;
	float m_Rotation;
};

}