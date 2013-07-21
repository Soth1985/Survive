#pragma once

#include <Survive/forward.h>
#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/oriented_box_shape.h>
#include <Survive/collision/convex_polygon_shape.h>
#include <Survive/collision/ray.h>
#include <Survive/collision/line_segment.h>

namespace Survive
{

class IntersectionTests
{
public:

	static bool IntersectAlignedBoxAlignedBox(const AlignedBoxShape& A, const AlignedBoxShape& B);

	static bool IntersectRayRay(const Ray& R1, const Ray& R2);

	static bool IntersectRayAlignedBox(const Ray& R, const AlignedBoxShape& B);

	static bool IntersectRayLineSegment(const Ray& R, const LineSegment& L);

	static bool IntersectRayOrientedBox(const Ray& R, const OrientedBoxShape& B);

	static bool IntersectRayConvexPolygon(const Ray& R, const ConvexPolygonShape& Poly);

	static bool IntersectConvexPolygonConvexPolygon(const ConvexPolygonShape& Poly1, const ConvexPolygonShape& Poly2);

	static bool IntersectLineSegmentLineSegment(const LineSegment& L1, const LineSegment& L2);

	static bool IntersectOrientedBoxOrientedBox(const OrientedBoxShape& Box1, const OrientedBoxShape& Box2);

	static bool IntersectOrientedBoxAlignedBox(const OrientedBoxShape& OB, const AlignedBoxShape& AB);

	static void Tests();
};

}