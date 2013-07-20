#pragma once

#include <Survive/forward.h>
#include <Survive/collision/aligned_box_shape.h>
#include <Survive/collision/oriented_box_shape.h>
#include <Survive/collision/ray.h>
#include <Survive/collision/line_segment.h>

namespace Survive
{

class IntersectionTests
{
public:

	static bool IntersectAlignedBoxAlignedBox(const AlignedBoxShape& A, const AlignedBoxShape& B);

	static bool IntersectRayRay(const Ray& R1, const Ray& R2);

	static bool IntersectLineSegmentLineSegment(const LineSegment& L1, const LineSegment& L2);

	static bool IntersectOrientedBoxOrientedBox(const OrientedBoxShape& Box1, const OrientedBoxShape& Box2);

	static void Tests();
};

}