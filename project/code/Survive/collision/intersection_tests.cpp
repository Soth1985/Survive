#include <Survive/collision/intersection_tests.h>
#include <Survive/collision/range.h>
#include <Survive/math_utils.h>

namespace Survive
{

static bool IsSegmentOnOneSide(const Ray& Axis, const LineSegment& Seg)
{ 
	sf::Vector2f D1 = Seg.GetPoint1() - Axis.GetPosition();
	sf::Vector2f D2 = Seg.GetPoint2() - Axis.GetPosition();
	sf::Vector2f N = MathUtils::GetVectorNormal(Axis.GetDirection());
	return MathUtils::DotProduct(N, D1) * MathUtils::DotProduct(N, D2) > 0;
}

static Range ProjectLineSegment(const LineSegment& Seg, const sf::Vector2f& Dir)
{
	sf::Vector2f DirUnit = MathUtils::Normalize(Dir);
	float Min = MathUtils::DotProduct(DirUnit, Seg.GetPoint1());
	float Max = MathUtils::DotProduct(DirUnit, Seg.GetPoint2());
	return Range(Min, Max);
}

static bool IsPointOnLineSegment(const sf::Vector2f& Point, const LineSegment& Seg)
{
	sf::Vector2f D = Seg.GetPoint2() - Seg.GetPoint1();
	sf::Vector2f Lp = Point - Seg.GetPoint1();
	sf::Vector2f Pr = MathUtils::ProjectVector(Lp, D);
	return MathUtils::AreClose(Lp, Pr) && MathUtils::Length(Pr) <= MathUtils::Length(D) && 0.0f <= MathUtils::DotProduct(Pr, D);
}

static bool EquivalentRays(const Ray& R1, const Ray& R2)
{ 
	if (!MathUtils::AreParallel(R1.GetDirection(), R2.GetDirection()))
		return false; 
	
	sf::Vector2f D = R1.GetPosition() - R2.GetPosition();
	return MathUtils::AreParallel(D, R1.GetDirection());
}

static LineSegment OrientedRectangleEdge(const OrientedBoxShape& Box, int nr)
{
	sf::Vector2f P1 = Box.GetHalfExtents();
	sf::Vector2f P2 = Box.GetHalfExtents();

	switch(nr % 4) 
	{
	case 0:/* top edge */
		P1.x = -P1.x;
		break;
	case 1:/* right edge */
		P2.y = -P2.y;
		break;
	case 2:/* bottom edge */
		P1.y = -P1.y;
		P2 = -P2;
		break;
	default:/* left edge */
		P1 = -P1;
		P2.x = -P2.x;
		break;
	}

	P1 = MathUtils::RotateVector(P1, Box.GetRotation());
	P1 = P1 + Box.GetCenter();

	P2 = MathUtils::RotateVector(P1, Box.GetRotation());
	P2 = P2 + Box.GetCenter();

	return LineSegment(P1, P2);
}

static bool SeparatingAxisForOrientedRectangle(const LineSegment& Axis, const OrientedBoxShape& Box)
{
	LineSegment Edge0 = OrientedRectangleEdge(Box, 0);
	LineSegment Edge2 = OrientedRectangleEdge(Box, 2);
	sf::Vector2f n = Axis.GetPoint1() - Axis.GetPoint2();

	n = MathUtils::Normalize(n);
	Range axisRange = ProjectLineSegment(Axis, n);
	Range Range0 = ProjectLineSegment(Edge0, n);
	Range Range2 = ProjectLineSegment(Edge2, n);
	Range Projection(Range0);
	Projection.Join(Range2);

	return !axisRange.Overlap(Projection);
}

bool IntersectionTests::IntersectAlignedBoxAlignedBox(const AlignedBoxShape& A, const AlignedBoxShape& B)
{
	float aLeft = A.GetCornerPosition().x;
	float aRight = aLeft + A.GetSize().x;
	float bLeft = B.GetCornerPosition().x;
	float bRight = bLeft + B.GetSize().x;
	float aBottom = A.GetCornerPosition().y;
	float aTop = aBottom + A.GetSize().y; 
	float bBottom = B.GetSize().y;
	float bTop = bBottom + B.GetSize().y;

	Range r11(aLeft, aRight);
	Range r12(bLeft, bRight);
	Range r21(aBottom, aTop);
	Range r22(bBottom, bTop);
	
	return r11.Overlap(r12) && r21.Overlap(r22);
}

bool IntersectionTests::IntersectRayRay(const Ray& R1, const Ray& R2)
{
	if (MathUtils::AreParallel(R1.GetDirection(), R2.GetDirection())) 
		return EquivalentRays(R1, R2); 
	else 
		return true;
}

bool IntersectionTests::IntersectLineSegmentLineSegment(const LineSegment& L1, const LineSegment& L2)
{
	Ray Axis1(L1.GetPoint1(), L1.GetPoint2() - L1.GetPoint1());

	if(0 == Axis1.GetDirection().x && 0 == Axis1.GetDirection().y)
		return IsPointOnLineSegment(L1.GetPoint1(), L2);
	else if(IsSegmentOnOneSide(Axis1, L2))
		return false;

	Ray Axis2(L2.GetPoint1(), L2.GetPoint2() - L2.GetPoint1());

	if(0 == Axis2.GetDirection().x && 0 == Axis2.GetDirection().y)
		return IsPointOnLineSegment(L2.GetPoint1(), L1);
	else if(IsSegmentOnOneSide(Axis2, L1))
		return false;

	if(MathUtils::AreParallel(Axis1.GetDirection(), Axis2.GetDirection()))
	{
		sf::Vector2f D =  MathUtils::Normalize(Axis1.GetDirection());
		Range RangeA = ProjectLineSegment(L1, D);
		Range RangeB = ProjectLineSegment(L2, D);
		return RangeA.Overlap(RangeB);
	}
	else
		return true;
}

bool IntersectionTests::IntersectOrientedBoxOrientedBox(const OrientedBoxShape& Box1, const OrientedBoxShape& Box2)
{
	LineSegment Edge = OrientedRectangleEdge(Box1, 0);

	if(SeparatingAxisForOrientedRectangle(Edge, Box2))
		return false;

	Edge = OrientedRectangleEdge(Box1, 1);
	if(SeparatingAxisForOrientedRectangle(Edge, Box2))
		return false;

	Edge = OrientedRectangleEdge(Box2, 0);
	if(SeparatingAxisForOrientedRectangle(Edge, Box1))
		return false;

	Edge = OrientedRectangleEdge(Box2, 1);

	return !SeparatingAxisForOrientedRectangle(Edge, Box1);
}

void IntersectionTests::Tests()
{
	//IntersectAlignedBoxAlignedBox
	{
		AlignedBoxShape A(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(4.0f, 4.0f));
		AlignedBoxShape B(sf::Vector2f(2.0f, 2.0f), sf::Vector2f(5.0f, 5.0f));
		AlignedBoxShape C(sf::Vector2f(6.0f, 4.0f), sf::Vector2f(4.0f, 2.0f));

		assert(IntersectAlignedBoxAlignedBox(A, B) == true);
		assert(IntersectAlignedBoxAlignedBox(B, C) == true);
		assert(IntersectAlignedBoxAlignedBox(A, C) == false);
	}

	//IntersectRayRay
	{
		sf::Vector2f a(3.0f, 5.0f);
		sf::Vector2f b(3.0f, 2.0f);
		sf::Vector2f c(8.0f, 4.0f);
		sf::Vector2f down(5.0f, -1.0f);
		sf::Vector2f up(5.0f, 2.0f);

		Ray R1(a, down);
		Ray R2(a, up);
		Ray R3(b, up);
		Ray R4(c, down);
		
		assert(IntersectRayRay(R1, R2) == true);
		assert(IntersectRayRay(R1, R3) == true);
		assert(IntersectRayRay(R2, R3) == false);
		assert(IntersectRayRay(R1, R4) == true); 
	}

	//IntersectLineSegmentLineSegment
	{
		sf::Vector2f a(3.0f, 4.0f);
		sf::Vector2f b(11, 1);
		sf::Vector2f c(8, 4);
		sf::Vector2f d(11, 7);
		
		LineSegment s1(a, b);
		LineSegment s2(c, d);
		
		assert(IntersectLineSegmentLineSegment( s1, s2)==false); 
	}

	//IntersectOrientedBoxOrientedBox
	{
		OrientedBoxShape a(sf::Vector2f(3.0f, 5.0f), sf::Vector2f(1.0f, 3.0f), 15.0f);
		OrientedBoxShape b(sf::Vector2f(10.0f, 5.0f), sf::Vector2f(2.0f, 2.0f), -15.0f);

		assert(IntersectOrientedBoxOrientedBox(a, b) == false);
	}
}

}