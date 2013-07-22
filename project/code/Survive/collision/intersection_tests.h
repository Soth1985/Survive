#pragma once

#include <Survive/forward.h>
#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/oriented_box_shape.h>
#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/collision/ray.h>
#include <Survive/collision/line_segment.h>
#include <Survive/collision/range.h>

namespace Survive
{

class IntersectionTests
{
public:

	static bool HasIntersectionRayRay(const Ray& R1, const Ray& R2);

	static bool HasIntersectionRayAlignedBox(const Ray& R, const AlignedBoxShape& InB, const sf::Transform& BTf);

	static bool HasIntersectionRayLineSegment(const Ray& R, const LineSegment& L);

	static bool HasIntersectionRayOrientedBox(const Ray& R, const OrientedBoxShape& InB, const sf::Transform& BTf);

	static bool HasIntersectionRayConvexPolygon(const Ray& R, const ConvexPolygonShape& InPoly, const sf::Transform& PolyTf);

	static bool HasIntersectionAlignedBoxAlignedBox(const AlignedBoxShape& InA, const sf::Transform& ATf, const AlignedBoxShape& InB, const sf::Transform& BTf);

	static bool HasIntersectionConvexPolygonConvexPolygon(const ConvexPolygonShape& InPoly1, const sf::Transform& Poly1Tf, const ConvexPolygonShape& InPoly2, const sf::Transform& Poly2Tf);

	static bool HasIntersectionOrientedBoxOrientedBox(const OrientedBoxShape& InBox1, const sf::Transform& Box1Tf, const OrientedBoxShape& InBox2, const sf::Transform& Box2Tf);

	static bool HasIntersectionOrientedBoxAlignedBox(const OrientedBoxShape& InOB, const sf::Transform& OBTf, const AlignedBoxShape& InAB, const sf::Transform& ABTf);

	static bool HasIntersectionShapeShape(const CollisionShape& Shape1, const sf::Transform& Shape1Tf, const CollisionShape& Shape2, const sf::Transform& Shape2Tf);

	static bool HasIntersectionLineSegmentLineSegment(const LineSegment& L1, const LineSegment& L2);

	static int FindIntersectionRayLineSegment(const Ray& R, const LineSegment& L1, float& Param);

	static int FindIntersectionRayAlignedBox(const Ray& R, const AlignedBoxShape& InBox, const sf::Transform& BoxTf, bool Closest, float& Param);

	static int FindIntersectionRayOrientedBox(const Ray& R, const OrientedBoxShape& InBox, const sf::Transform& BoxTf, bool Closest, float& Param);

	static int FindIntersectionRayConvexPolygon(const Ray& R, const ConvexPolygonShape& InPoly, const sf::Transform& PolyTf, bool Closest, float& Param);

	static int FindIntersectionRayShape(const Ray& R, const CollisionShape& Shape, const sf::Transform& ShapeTf, bool Closest, float& Param);

	static Range ComputeInterval(const ConvexPolygonShape& C, const sf::Vector2f& D);

	static void Tests();
};

}