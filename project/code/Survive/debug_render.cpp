#include <Survive/debug_render.h>
#include <Survive/math_utils.h>

#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/oriented_box_shape.h>
#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/collision/ray.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

template <class T>
void UpdateShapeList(std::list<T>& List, float Dt)
{
	std::list<T>::iterator It = List.begin();

	while (It != List.end())
	{
		It->m_LifeTime -= Dt;
		
		if (It->m_LifeTime <= 0.0f)
		{
			It = List.erase(It);
		}
		else
			++It;
	}
}

template <class T>
void DrawShapeList(std::list<T>& List, sf::RenderWindow* pWindow)
{
	for (std::list<T>::iterator It = List.begin(); It != List.end(); ++It)
	{
		if (It->m_Fill)
			It->m_Shape.setFillColor(It->m_Color);
		else
			It->m_Shape.setFillColor(sf::Color::Transparent);

		It->m_Shape.setOutlineThickness(2);
		It->m_Shape.setOutlineColor(It->m_Color);
		pWindow->draw(It->m_Shape);
	}
}

template <class SfShapeT>
void ApplyTransform(SfShapeT& Shape, const sf::Transform& Tf)
{
	Shape.setPosition(Shape.getPosition() + MathUtils::GetTranslation(Tf));
	//Shape.setScale(MathUtils::GetScale(Tf));
	Shape.setRotation(MathUtils::GetRotation(Tf));
}

DebugRender::DebugRender(const sf::Font* pTextFont)
	:
m_pFont(pTextFont),
m_IsEnabled(false)
{

}

DebugRender::~DebugRender()
{

}

void DebugRender::AddRay(const Ray& R, float Len, float LifeTime, const sf::Color& Color)
{
	if (!m_IsEnabled)
		return;

	m_Lines.push_back(ShapeHolder<LineSegment>(LineSegment(), LifeTime, Color, false));
	m_Lines.back().m_Shape.SetPoint1(R.GetPosition());
	m_Lines.back().m_Shape.SetPoint2(R.GetPosition() + R.GetDirection() * Len);
}

void DebugRender::AddLine(const LineSegment& L, float LifeTime, const sf::Color& Color)
{
	if (!m_IsEnabled)
		return;

	m_Lines.push_back(ShapeHolder<LineSegment>(L, LifeTime, Color, false));
}
	
void DebugRender::AddAlignedBox(const AlignedBoxShape& Box, const sf::Transform& Tf, float LifeTime, const sf::Color& Color, bool Fill)
{
	if (!m_IsEnabled)
		return;

	m_Boxes.push_back(ShapeHolder<sf::RectangleShape>(sf::RectangleShape(Box.GetSize()), LifeTime, Color, Fill));
	m_Boxes.back().m_Shape.setPosition(Box.GetCornerPosition());
	ApplyTransform(m_Boxes.back().m_Shape, Tf);
}

void DebugRender::AddOrientedBox(const OrientedBoxShape& Box, const sf::Transform& Tf, float LifeTime, const sf::Color& Color, bool Fill)
{
	if (!m_IsEnabled)
		return;

	m_Boxes.push_back(ShapeHolder<sf::RectangleShape>(sf::RectangleShape(Box.GetHalfExtents() * 2.0f), LifeTime, Color, Fill));
	m_Boxes.back().m_Shape.setPosition(Box.GetCenter());
	ApplyTransform(m_Boxes.back().m_Shape, Tf);
}
	
void DebugRender::AddConvexPolygon(const ConvexPolygonShape& Poly, const sf::Transform& Tf, float LifeTime, const sf::Color& Color, bool Fill)
{
	if (!m_IsEnabled)
		return;

	m_ConvexPolygons.push_back(ShapeHolder<sf::ConvexShape>(sf::ConvexShape(Poly.GetPointC()), LifeTime, Color, Fill));

	for (size_t Idx = 0; Idx < Poly.GetPointC(); ++Idx)
	{
		m_ConvexPolygons.back().m_Shape.setPoint(Idx, Poly[Idx]);
	}

	ApplyTransform(m_ConvexPolygons.back().m_Shape, Tf);
}
	
void DebugRender::AddCircle(const sf::Vector2f& Pos, float Radius, float LifeTime, const sf::Color& Color, bool Fill)
{
	if (!m_IsEnabled)
		return;

	m_Circles.push_back(ShapeHolder<sf::CircleShape>(sf::CircleShape(Radius), LifeTime, Color, Fill));
	m_Circles.back().m_Shape.setPosition(Pos - sf::Vector2f(Radius, Radius));
}
	
void DebugRender::AddText(const std::string& Text, const sf::Transform& Tf, unsigned int CharacterSize, float LifeTime, const sf::Color& Color, bool Fill)
{
	if (!m_IsEnabled)
		return;

	m_Texts.push_back(ShapeHolder<sf::Text>(sf::Text(Text, *m_pFont, CharacterSize), LifeTime, Color, Fill));
	ApplyTransform(m_Texts.back().m_Shape, Tf);
}

void DebugRender::Update(float Dt)
{
	if (!m_IsEnabled)
		return;

	UpdateShapeList(m_Texts, Dt);
	UpdateShapeList(m_Lines, Dt);
	UpdateShapeList(m_Boxes, Dt);
	UpdateShapeList(m_ConvexPolygons, Dt);
	UpdateShapeList(m_Circles, Dt);
}

void DebugRender::Draw(sf::RenderWindow* pWindow)
{
	if (!m_IsEnabled)
		return;

	for (auto It = m_Lines.begin(); It != m_Lines.end(); ++It)
	{
		sf::Vertex Line[] =
		{
			sf::Vertex(It->m_Shape.GetPoint1(), It->m_Color),
			sf::Vertex(It->m_Shape.GetPoint2(), It->m_Color)
		};

		pWindow->draw(Line, 2, sf::Lines);
	}

	DrawShapeList(m_Circles, pWindow);
	DrawShapeList(m_Boxes, pWindow);
	DrawShapeList(m_ConvexPolygons, pWindow);

	for (auto It = m_Texts.begin(); It != m_Texts.end(); ++It)
	{
		It->m_Shape.setColor(It->m_Color);
		pWindow->draw(It->m_Shape);
	}
}

}