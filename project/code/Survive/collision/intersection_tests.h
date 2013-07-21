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

	static bool HasIntersectionAlignedBoxAlignedBox(const AlignedBoxShape& A, const AlignedBoxShape& B);

	static bool HasIntersectionRayRay(const Ray& R1, const Ray& R2);

	static bool HasIntersectionRayAlignedBox(const Ray& R, const AlignedBoxShape& B);

	static bool HasIntersectionRayLineSegment(const Ray& R, const LineSegment& L);

	static bool HasIntersectionRayOrientedBox(const Ray& R, const OrientedBoxShape& B);

	static bool HasIntersectionRayConvexPolygon(const Ray& R, const ConvexPolygonShape& Poly);

	static bool HasIntersectionConvexPolygonConvexPolygon(const ConvexPolygonShape& Poly1, const ConvexPolygonShape& Poly2);

	static bool HasIntersectioLineSegmentLineSegment(const LineSegment& L1, const LineSegment& L2);

	static bool HasIntersectionOrientedBoxOrientedBox(const OrientedBoxShape& Box1, const OrientedBoxShape& Box2);

	static bool HasIntersectionOrientedBoxAlignedBox(const OrientedBoxShape& OB, const AlignedBoxShape& AB);

	static int FindIntersectionRayLineSegment(const Ray& R, const LineSegment& L1, float& Param);

	static int FindIntersectionRayAlignedBox(const Ray& R, const AlignedBoxShape& Box, float& Param);

	static int FindIntersectionRayOrientedBox(const Ray& R, const OrientedBoxShape& Box, float& Param);

	static int FindIntersectionRayConvexPolygon(const Ray& R, const ConvexPolygonShape& Poly, float& Param);

	static Range ComputeInterval(const ConvexPolygonShape& C, const sf::Vector2f& D);

	static void Tests();
};

}