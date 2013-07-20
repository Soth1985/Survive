#pragma once

#include <Survive/forward.h>
#include <Survive/collision/collision_shape.h>

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

	AlignedBoxShape(const sf::Vector2f& CorenerPosition, const sf::Vector2f& Size)
		:
	m_CornerPosition(CorenerPosition),
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

	void Extend(const sf::Vector2f& Point);

	void Extend(const AlignedBoxShape& Box);

private:

	sf::Vector2f m_CornerPosition;
	sf::Vector2f m_Size;
};

}