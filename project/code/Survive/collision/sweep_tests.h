#pragma once

#include <Survive/forward.h>
#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/oriented_box_shape.h>
#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/collision/ray.h>
#include <Survive/collision/line_segment.h>

namespace Survive
{

class SweepTests
{
public:

	int SweepConvexPolygonConvexPolygon(const ConvexPolygonShape& P1, const ConvexPolygonShape& P2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	int SweepAlignedBoxConvexPolygon(const AlignedBoxShape& Box, const ConvexPolygonShape& P, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	int SweepOrientedBoxConvexPolygon(const OrientedBoxShape& Box, const ConvexPolygonShape& P, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	int SweepOrientedBoxOrientedBox(const OrientedBoxShape& Box1, const OrientedBoxShape& Box2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	int SweepAlignedBoxAlignedBox(const AlignedBoxShape& Box1, const AlignedBoxShape& Box2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	int SweepAlignedBoxOrientedBox(const AlignedBoxShape& Box1, const OrientedBoxShape& Box2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);

private:

	static ConvexPolygonShape m_TempShape1;
	static ConvexPolygonShape m_TempShape2;
};

};