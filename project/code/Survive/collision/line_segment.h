#pragma once

#include <Survive/forward.h>

#include <SFML/System/Vector2.hpp>

namespace Survive
{

class LineSegment
{
public:

	LineSegment()
	{

	}

	LineSegment(const sf::Vector2f& Point1, const sf::Vector2f& Point2)
		:
	m_Point1(Point1),
	m_Point2(Point2)
	{

	}

	const sf::Vector2f& GetPoint1()const
	{
		return m_Point1;
	}

	void SetPoint1(const sf::Vector2f& Point1)
	{
		m_Point1 = Point1;
	}

	const sf::Vector2f& GetPoint2()const
	{
		return m_Point2;
	}

	void SetPoint2(const sf::Vector2f& Point2)
	{
		m_Point2 = Point2;
	}

private:
	sf::Vector2f m_Point1;
	sf::Vector2f m_Point2;
};

}