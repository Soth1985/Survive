#pragma once

#include <Survive/forward.h>

#include <Survive/collision/line_segment.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Survive
{

class DebugRender
{
public:

	DebugRender(const sf::Font* pTextFont);

	~DebugRender();

	void AddRay(const Ray& R, float Len, float LifeTime, const sf::Color& Color = sf::Color::White);

	void AddLine(const LineSegment& L, float LifeTime, const sf::Color& Color = sf::Color::White);
	
	void AddAlignedBox(const AlignedBoxShape& Box, const sf::Transform& Tf, float LifeTime, const sf::Color& Color = sf::Color::White, bool Fill = false);

	void AddOrientedBox(const OrientedBoxShape& Box, const sf::Transform& Tf, float LifeTime, const sf::Color& Color = sf::Color::White, bool Fill = false);
	
	void AddConvexPolygon(const ConvexPolygonShape& Poly, const sf::Transform& Tf, float LifeTime, const sf::Color& Color = sf::Color::White, bool Fill = false);
	
	void AddCircle(const sf::Vector2f& Pos, float Radius, float LifeTime, const sf::Color& Color = sf::Color::White, bool Fill = false);
	
	void AddText(const std::string& Text, const sf::Transform& Tf, unsigned int CharacterSize, float LifeTime, const sf::Color& Color = sf::Color::White, bool Fill = false);

	void Update(float Dt);

	void Draw(sf::RenderWindow* pWindow);

	bool GetEnabled()const
	{
		return m_IsEnabled;
	}

	void SetEnabled(bool Enabled)
	{
		m_IsEnabled = Enabled;
	}

private:

	template<class T>
	struct ShapeHolder
	{
		ShapeHolder()
			:
		m_LifeTime(0.0f),
		m_Fill(false)
		{

		}

		ShapeHolder(const T& Shape, float LifeTime, const sf::Color& Color, bool Fill)
			:
		m_Shape(Shape),
		m_LifeTime(LifeTime),
		m_Color(Color),
		m_Fill(Fill)
		{

		}

		T m_Shape;
		float m_LifeTime;
		sf::Color m_Color;
		bool m_Fill;
	};

	typedef std::list< ShapeHolder<LineSegment> > Lines;
	typedef std::list< ShapeHolder<sf::RectangleShape> > Boxes;
	typedef std::list< ShapeHolder<sf::ConvexShape> > ConvexPolygons;
	typedef std::list< ShapeHolder<sf::CircleShape> > Circles;
	typedef std::list< ShapeHolder<sf::Text> > Texts;

	Lines m_Lines;
	Boxes m_Boxes;
	ConvexPolygons m_ConvexPolygons;
	Circles m_Circles;
	Texts m_Texts;
	const sf::Font* m_pFont;
	bool m_IsEnabled;
};

}