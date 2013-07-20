#pragma once

#include <Survive/forward.h>

#include <SFML/System/Vector2.hpp>

namespace Survive
{

class Ray
{
public:

	Ray()
	{

	}

	Ray(const sf::Vector2f& Position, const sf::Vector2f& Direction)
		:
	m_Position(Position),
	m_Direction(Direction)
	{

	}

	const sf::Vector2f& GetPosition()const
	{
		return m_Position;
	}

	void SetPosition(const sf::Vector2f& Position)
	{
		m_Position = Position;
	}

	const sf::Vector2f& GetDirection()const
	{
		return m_Direction;
	}

	void SetDirection(const sf::Vector2f& Direction)
	{
		m_Direction = Direction;
	}

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
};

}