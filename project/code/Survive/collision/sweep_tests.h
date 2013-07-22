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

	static int SweepConvexPolygonConvexPolygon(const ConvexPolygonShape& InP1, const sf::Transform& P1Tf, const ConvexPolygonShape& InP2, const sf::Transform& P2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);

	static int SweepAlignedBoxConvexPolygon(const AlignedBoxShape& InBox, const sf::Transform& BoxTf, const ConvexPolygonShape& InP, const sf::Transform& PTf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	
	static int SweepOrientedBoxConvexPolygon(const OrientedBoxShape& InBox, const sf::Transform& BoxTf, const ConvexPolygonShape& InP, const sf::Transform& PTf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	
	static int SweepOrientedBoxOrientedBox(const OrientedBoxShape& InBox1, const sf::Transform& Box1Tf, const OrientedBoxShape& InBox2, const sf::Transform& Box2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	
	static int SweepAlignedBoxAlignedBox(const AlignedBoxShape& InBox1, const sf::Transform& Box1Tf, const AlignedBoxShape& InBox2, const sf::Transform& Box2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	
	static int SweepAlignedBoxOrientedBox(const AlignedBoxShape& InBox1, const sf::Transform& Box1Tf, const OrientedBoxShape& InBox2, const sf::Transform& Box2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
	
	static int SweepShapeShape(const CollisionShape& Shape1, const sf::Transform& Shape1Tf, const CollisionShape& Shape2, const sf::Transform& Shape2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast);
};

};