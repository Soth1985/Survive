#include <Survive/collision/intersection_tests.h>
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

static bool SeparatingAxisForOrientedBox(const LineSegment& Axis, const OrientedBoxShape& Box)
{
	LineSegment Edge0 = Box.GetEdge(0);
	LineSegment Edge2 = Box.GetEdge(2);
	sf::Vector2f N = Axis.GetPoint1() - Axis.GetPoint2();

	N = MathUtils::Normalize(N);
	Range AxisRange = ProjectLineSegment(Axis, N);
	Range Range0 = ProjectLineSegment(Edge0, N);
	Range Range2 = ProjectLineSegment(Edge2, N);
	Range Projection(Range0);
	Projection.Join(Range2);

	return !AxisRange.Overlap(Projection);
}

static bool SeparatingAxisForAlignedBox(const LineSegment& Axis, const AlignedBoxShape& Box)
{
	sf::Vector2f N = Axis.GetPoint1() - Axis.GetPoint2();

	N = MathUtils::Normalize(N);

	LineSegment EdgeA(Box.GetCorner(0), Box.GetCorner(1));
	LineSegment EdgeB(Box.GetCorner(2), Box.GetCorner(3));

	Range EdgeARange = ProjectLineSegment(EdgeA, N);
	Range EdgeBRange = ProjectLineSegment(EdgeB, N);
	Range Projection(EdgeARange);
	Projection.Join(EdgeBRange);

	Range AxisRange = ProjectLineSegment(Axis, N);

	return !AxisRange.Overlap(Projection);
}

static int FindIntersectionLineLine(const sf::Vector2f& P1, const sf::Vector2f& D1, const sf::Vector2f& P2, const sf::Vector2f& D2, float& Param1)
{
	sf::Vector2f E = P2 - P1;
	float Kross = D1.x * D2.y - D1.y * D2.x;
	float SqrKross = Kross * Kross;
	float SqrLen0 = D1.x * D1.x + D1.y * D1.y;
	float SqrLen1 = D2.x * D2.x + D2.y * D2.y;
	const float SqrEpsilon = 0.0001f;

	if (SqrKross > SqrEpsilon * SqrLen0 * SqrLen1)
	{
		// lines are not parallel
		Param1 = (E.x * D2.y - E.y * D2.x) / Kross;
		return 1;
	}

	// lines are parallel
	float SqrLenE = E.x * E.x + E.y * E.y;
	Kross = E.x * D1.y - E.y * D1.x;
	SqrKross = Kross * Kross;

	if (SqrKross > SqrEpsilon * SqrLen0 * SqrLenE)
	{
		// lines are different
		return 0;
	}

	//lines are same
	return 2;
}

Range IntersectionTests::ComputeInterval(const ConvexPolygonShape& C, const sf::Vector2f& D)
{
	float Min = MathUtils::DotProduct(D, C[0]);
	float Max = Min;

	for (size_t Idx = 1; Idx < C.GetPointC(); ++Idx)
	{
		float Value = MathUtils::DotProduct(D, C[Idx]);

		if (Value < Min)
			Min = Value;
		else if (Value > Max)
			Max = Value;
	}

	return Range(Min, Max);
}

bool IntersectionTests::HasIntersectionAlignedBoxAlignedBox(const AlignedBoxShape& InA, const sf::Transform& ATf, const AlignedBoxShape& InB, const sf::Transform& BTf)
{
	AlignedBoxShape A(InA);
	A.TransformShape(ATf);
	AlignedBoxShape B(InB);
	B.TransformShape(BTf);

	float LeftA = A.GetCornerPosition().x;
	float RightA = LeftA + A.GetSize().x;
	float LeftB = B.GetCornerPosition().x;
	float RightB = LeftB + B.GetSize().x;
	float BottomA = A.GetCornerPosition().y;
	float TopA = BottomA + A.GetSize().y; 
	float BottomB = B.GetSize().y;
	float TopB = BottomB + B.GetSize().y;

	Range R11(LeftA, RightA);
	Range R12(LeftB, RightB);
	Range R21(BottomA, TopA);
	Range R22(BottomB, TopB);
	
	return R11.Overlap(R12) && R21.Overlap(R22);
}

bool IntersectionTests::HasIntersectionRayRay(const Ray& R1, const Ray& R2)
{
	if (MathUtils::AreParallel(R1.GetDirection(), R2.GetDirection())) 
		return EquivalentRays(R1, R2); 
	else 
		return true;
}

bool IntersectionTests::HasIntersectionLineSegmentLineSegment(const LineSegment& L1, const LineSegment& L2)
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

bool IntersectionTests::HasIntersectionOrientedBoxOrientedBox(const OrientedBoxShape& InBox1, const sf::Transform& Box1Tf, const OrientedBoxShape& InBox2, const sf::Transform& Box2Tf)
{
	OrientedBoxShape Box1(InBox1);
	Box1.TransformShape(Box1Tf);
	OrientedBoxShape Box2(InBox2);
	Box1.TransformShape(Box2Tf);

	LineSegment Edge = Box1.GetEdge(0);

	if(SeparatingAxisForOrientedBox(Edge, Box2))
		return false;

	Edge = Box1.GetEdge(1);
	if(SeparatingAxisForOrientedBox(Edge, Box2))
		return false;

	Edge = Box2.GetEdge(0);
	if(SeparatingAxisForOrientedBox(Edge, Box1))
		return false;

	Edge = Box2.GetEdge(1);

	return !SeparatingAxisForOrientedBox(Edge, Box1);
}

bool IntersectionTests::HasIntersectionRayAlignedBox(const Ray& R, const AlignedBoxShape& InB, const sf::Transform& BTf)
{
	AlignedBoxShape B(InB);
	B.TransformShape(BTf);

	sf::Vector2f N = MathUtils::GetVectorNormal(R.GetDirection());

	sf::Vector2f C1 = B.GetCornerPosition();
	sf::Vector2f C2 = C1 + B.GetSize();
	sf::Vector2f C3(C2.x, C1.y);
	sf::Vector2f C4(C1.x, C2.y);

	C1 = C1 - R.GetPosition();
	C2 = C2 - R.GetPosition();
	C3 = C3 - R.GetPosition();
	C4 = C4 - R.GetPosition();

	float Dp1 = MathUtils::DotProduct(N, C1);
	float Dp2 = MathUtils::DotProduct(N, C2);
	float Dp3 = MathUtils::DotProduct(N, C3);
	float Dp4 = MathUtils::DotProduct(N, C4);

	return (Dp1 * Dp2 <= 0) || (Dp2 * Dp3 <= 0) || (Dp3 * Dp4 <= 0);
}

bool IntersectionTests::HasIntersectionRayLineSegment(const Ray& R, const LineSegment& L)
{
	return !IsSegmentOnOneSide(R, L);
}

bool IntersectionTests::HasIntersectionRayOrientedBox(const Ray& R, const OrientedBoxShape& InB, const sf::Transform& BTf)
{
	OrientedBoxShape B(InB);
	B.TransformShape(BTf);

	AlignedBoxShape AlignedB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(B.GetHalfExtents().x * 2, B.GetHalfExtents().y * 2));

	sf::Vector2f RotatedRPos = R.GetPosition() - B.GetCenter();
	RotatedRPos = MathUtils::RotateVector(RotatedRPos, -B.GetRotation());
	RotatedRPos = RotatedRPos + B.GetHalfExtents();

	sf::Vector2f RotatedRDir = MathUtils::RotateVector(R.GetDirection(), -B.GetRotation());

	Ray RotatedR(RotatedRPos, RotatedRDir);

	return HasIntersectionRayAlignedBox(RotatedR, AlignedB, sf::Transform::Identity);
}

bool IntersectionTests::HasIntersectionOrientedBoxAlignedBox(const OrientedBoxShape& InOB, const sf::Transform& OBTf, const AlignedBoxShape& InAB, const sf::Transform& ABTf)
{
	OrientedBoxShape OB(InOB);
	OB.TransformShape(OBTf);
	AlignedBoxShape AB(InAB);
	AB.TransformShape(ABTf);

	AlignedBoxShape Hull;
	
	OB.GetAlignedHull(&Hull);

	if(!HasIntersectionAlignedBoxAlignedBox(Hull, sf::Transform::Identity, AB, sf::Transform::Identity))
		return false;

	LineSegment edge = OB.GetEdge(0);

	if(SeparatingAxisForAlignedBox(edge, AB))
		return false;

	edge = OB.GetEdge(1);

	return !SeparatingAxisForAlignedBox(edge, AB);
}

bool IntersectionTests::HasIntersectionRayConvexPolygon(const Ray& R, const ConvexPolygonShape& InPoly, const sf::Transform& PolyTf)
{
	ConvexPolygonShape Poly(InPoly);
	Poly.TransformShape(PolyTf);

	for (size_t Idx0 = 0, Idx1 = Poly.GetPointC() - 1; Idx0 < Poly.GetPointC(); Idx1 = Idx0, ++Idx0) 
	{
		if (HasIntersectionRayLineSegment(R, LineSegment(Poly[Idx0], Poly[Idx1])))
		{
			return true;
		}
	}

	return false;
}

bool IntersectionTests::HasIntersectionConvexPolygonConvexPolygon(const ConvexPolygonShape& InPoly1, const sf::Transform& Poly1Tf, const ConvexPolygonShape& InPoly2, const sf::Transform& Poly2Tf)
{
	ConvexPolygonShape Poly1(InPoly1);
	Poly1.TransformShape(Poly1Tf);
	ConvexPolygonShape Poly2(InPoly2);
	Poly2.TransformShape(Poly2Tf);

	for (size_t Idx0 = 0, Idx1 = Poly1.GetPointC() - 1; Idx0 < Poly1.GetPointC(); Idx1 = Idx0, ++Idx0) 
	{
		sf::Vector2f Edge = Poly1[Idx0] - Poly1[Idx1];
		sf::Vector2f D = MathUtils::GetVectorNormal(Edge);
		Range R1 = ComputeInterval(Poly1, D);
		Range R2 = ComputeInterval(Poly2, D);
		if (!R1.Overlap(R2))
			return false;
	}

	for (size_t Idx0 = 0, Idx1 = Poly2.GetPointC() - 1; Idx0 < Poly2.GetPointC(); Idx1 = Idx0, ++Idx0)
	{
		sf::Vector2f Edge = Poly2[Idx0] - Poly2[Idx1];
		sf::Vector2f D = MathUtils::GetVectorNormal(Edge);
		Range R1 = ComputeInterval(Poly1, D);
		Range R2 = ComputeInterval(Poly2, D);
		if (!R1.Overlap(R2))
			return false;
	}

	return true;
}

int IntersectionTests::FindIntersectionRayLineSegment(const Ray& R, const LineSegment& L1, float& Param)
{
	int result = FindIntersectionLineLine(R.GetPosition(), R.GetDirection(), L1.GetPoint1(), L1.GetPoint2() - L1.GetPoint1(), Param);

	if (result == 1 && Param < 0.0f)
		result = 0;

	return result;
}

int IntersectionTests::FindIntersectionRayAlignedBox(const Ray& R, const AlignedBoxShape& InBox, const sf::Transform& BoxTf, bool Closest, float& Param)
{
	AlignedBoxShape Box(InBox);
	Box.TransformShape(BoxTf);

	int Result = 0;

	float ClosestCollision = FLT_MAX;

	for(int EdgeIdx = 0; EdgeIdx < 4; ++EdgeIdx)
	{
		Param = FLT_MAX;
		Result = FindIntersectionRayLineSegment(R, Box.GetEdge(EdgeIdx), Param);

		if (Result == 1)
		{
			if (Param < ClosestCollision)
				ClosestCollision = Param;

			if (!Closest)
				return 1;
		}
		else
			Result = 0;
	}

	return Result;
}

int IntersectionTests::FindIntersectionRayOrientedBox(const Ray& R, const OrientedBoxShape& InBox, const sf::Transform& BoxTf, bool Closest, float& Param)
{
	OrientedBoxShape Box(InBox);
	Box.TransformShape(BoxTf);

	AlignedBoxShape AlignedB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(Box.GetHalfExtents().x * 2.0f, Box.GetHalfExtents().y * 2.0f));

	sf::Vector2f RotatedRPos = R.GetPosition() - Box.GetCenter();
	RotatedRPos = MathUtils::RotateVector(RotatedRPos, -Box.GetRotation());
	RotatedRPos = RotatedRPos + Box.GetHalfExtents();

	sf::Vector2f RotatedRDir = MathUtils::RotateVector(R.GetDirection(), -Box.GetRotation());

	Ray RotatedR(RotatedRPos, RotatedRDir);

	return FindIntersectionRayAlignedBox(R, AlignedB, sf::Transform::Identity, Closest, Param);
}

int IntersectionTests::FindIntersectionRayConvexPolygon(const Ray& R, const ConvexPolygonShape& InPoly, const sf::Transform& PolyTf, bool Closest, float& Param)
{
	ConvexPolygonShape Poly(InPoly);
	Poly.TransformShape(PolyTf);

	int Result = 0;

	float ClosestCollision = FLT_MAX;

	for (size_t Idx0 = 0, Idx1 = Poly.GetPointC() - 1; Idx0 < Poly.GetPointC(); Idx1 = Idx0, ++Idx0)
	{
		Param = FLT_MAX;
		Result = FindIntersectionRayLineSegment(R, LineSegment(Poly[Idx0], Poly[Idx1]), Param);

		if (Result == 1)
		{
			if (Param < ClosestCollision)
				ClosestCollision = Param;

			if (!Closest)
				return 1;
		}
		else
			Result = 0;
	}

	return Result;
}

int IntersectionTests::FindIntersectionRayShape(const Ray& R, const CollisionShape& Shape, const sf::Transform& ShapeTf, bool Closest, float& Param)
{
	const AlignedBoxShape* Aligned = TypeCast<AlignedBoxShape>(&Shape);

	if (Aligned)
		return FindIntersectionRayAlignedBox(R, *Aligned, ShapeTf, Closest, Param);

	const ConvexPolygonShape* Convex = TypeCast<ConvexPolygonShape>(&Shape);

	if (Convex)
		return FindIntersectionRayConvexPolygon(R, *Convex, ShapeTf, Closest, Param);

	const OrientedBoxShape* Oriented = TypeCast<OrientedBoxShape>(&Shape);

	if (Oriented)
		return FindIntersectionRayOrientedBox(R, *Oriented, ShapeTf, Closest, Param);

	return 0;
}

bool IntersectionTests::HasIntersectionShapeShape(const CollisionShape& Shape1, const sf::Transform& Shape1Tf, const CollisionShape& Shape2, const sf::Transform& Shape2Tf)
{
	const AlignedBoxShape* Aligned1 = TypeCast<AlignedBoxShape>(&Shape1);

	if (Aligned1)
	{
		const AlignedBoxShape* Aligned2 = TypeCast<AlignedBoxShape>(&Shape2);

		if (Aligned2)
			return HasIntersectionAlignedBoxAlignedBox(*Aligned1, Shape1Tf, *Aligned2, Shape2Tf);

		const ConvexPolygonShape* Convex2 = TypeCast<ConvexPolygonShape>(&Shape2);

		if (Convex2)
		{
			ConvexPolygonShape TempShape(4);
			Aligned1->ToConvex(&TempShape);
			return HasIntersectionConvexPolygonConvexPolygon(TempShape, Shape1Tf, *Convex2, Shape2Tf);
		}

		const OrientedBoxShape* Oriented2 = TypeCast<OrientedBoxShape>(&Shape2);

		if (Oriented2)
			return HasIntersectionOrientedBoxAlignedBox(*Oriented2, Shape2Tf, *Aligned1, Shape1Tf); 
	}

	const ConvexPolygonShape* Convex1 = TypeCast<ConvexPolygonShape>(&Shape1);

	if (Convex1)
	{
		const AlignedBoxShape* Aligned2 = TypeCast<AlignedBoxShape>(&Shape2);

		if (Aligned2)
		{
			ConvexPolygonShape TempShape(4);
			Aligned2->ToConvex(&TempShape);
			return HasIntersectionConvexPolygonConvexPolygon(*Convex1, Shape1Tf, TempShape, Shape2Tf);
		}

		const ConvexPolygonShape* Convex2 = TypeCast<ConvexPolygonShape>(&Shape2);

		if (Convex2)
		{
			return HasIntersectionConvexPolygonConvexPolygon(*Convex1, Shape1Tf, *Convex2, Shape2Tf);
		}

		const OrientedBoxShape* Oriented2 = TypeCast<OrientedBoxShape>(&Shape2);

		if (Oriented2)
		{
			ConvexPolygonShape TempShape(4);
			Oriented2->ToConvex(&TempShape);
			return HasIntersectionConvexPolygonConvexPolygon(*Convex1, Shape1Tf, TempShape, Shape2Tf);
		}
	}

	const OrientedBoxShape* Oriented1 = TypeCast<OrientedBoxShape>(&Shape1);

	if (Oriented1)
	{
		const AlignedBoxShape* Aligned2 = TypeCast<AlignedBoxShape>(&Shape2);

		if (Aligned2)
			return HasIntersectionOrientedBoxAlignedBox(*Oriented1, Shape1Tf, *Aligned2, Shape2Tf);

		const ConvexPolygonShape* Convex2 = TypeCast<ConvexPolygonShape>(&Shape2);

		if (Convex2)
		{
			ConvexPolygonShape TempShape(4);
			Oriented1->ToConvex(&TempShape);
			return HasIntersectionConvexPolygonConvexPolygon(TempShape, Shape1Tf, *Convex2, Shape2Tf);
		}

		const OrientedBoxShape* Oriented2 = TypeCast<OrientedBoxShape>(&Shape2);

		if (Oriented2)
			return HasIntersectionOrientedBoxOrientedBox(*Oriented1, Shape1Tf, *Oriented2, Shape2Tf); 
	}

	return false;
}

void IntersectionTests::Tests()
{
	//IntersectAlignedBoxAlignedBox
	{
		AlignedBoxShape A(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(4.0f, 4.0f));
		AlignedBoxShape B(sf::Vector2f(2.0f, 2.0f), sf::Vector2f(5.0f, 5.0f));
		AlignedBoxShape C(sf::Vector2f(6.0f, 4.0f), sf::Vector2f(4.0f, 2.0f));

		assert(HasIntersectionAlignedBoxAlignedBox(A, sf::Transform::Identity, B, sf::Transform::Identity) == true);
		assert(HasIntersectionAlignedBoxAlignedBox(B, sf::Transform::Identity, C, sf::Transform::Identity) == true);
		assert(HasIntersectionAlignedBoxAlignedBox(A, sf::Transform::Identity, C, sf::Transform::Identity) == false);
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
		
		assert(HasIntersectionRayRay(R1, R2) == true);
		assert(HasIntersectionRayRay(R1, R3) == true);
		assert(HasIntersectionRayRay(R2, R3) == false);
		assert(HasIntersectionRayRay(R1, R4) == true); 
	}

	//IntersectLineSegmentLineSegment
	{
		sf::Vector2f a(3.0f, 4.0f);
		sf::Vector2f b(11, 1);
		sf::Vector2f c(8, 4);
		sf::Vector2f d(11, 7);
		
		LineSegment s1(a, b);
		LineSegment s2(c, d);
		
		assert(HasIntersectionLineSegmentLineSegment( s1, s2)==false); 
	}

	//IntersectOrientedBoxOrientedBox
	{
		OrientedBoxShape a(sf::Vector2f(3.0f, 5.0f), sf::Vector2f(1.0f, 3.0f), 15.0f);
		OrientedBoxShape b(sf::Vector2f(10.0f, 5.0f), sf::Vector2f(2.0f, 2.0f), -15.0f);

		assert(HasIntersectionOrientedBoxOrientedBox(a, sf::Transform::Identity, b, sf::Transform::Identity) == false);
	}

	//IntersectRayAlignedBox
	{
		Ray r(sf::Vector2f(6.0f, 8.0f), sf::Vector2f(2.0f, -3.0f));
		AlignedBoxShape box(sf::Vector2f(3.0f, 2.0f), sf::Vector2f(6.0f, 4.0f));
		
		assert(HasIntersectionRayAlignedBox(r, box, sf::Transform::Identity) == true);
	}

	//IntersectRayLineSegment
	{
		sf::Vector2f base(3.0f, 4.0f);
		sf::Vector2f direction(4.0f, -2.0f);
		sf::Vector2f point1(8.0f, 4.0f);
		sf::Vector2f point2(11.0f, 7.0f);
		
		LineSegment s(point1, point2);
		Ray l(base, direction);

		assert(HasIntersectionRayLineSegment(l, s) == false);
	}

	//IntersectRayOrientedBox
	{
		Ray r(sf::Vector2f(7.0f, 3.0f), sf::Vector2f(2.0f, -1.0f));
		OrientedBoxShape b(sf::Vector2f(5.0f, 4.0f), sf::Vector2f(3.0f, 2.0f), 30.0f);
		
		assert(HasIntersectionRayOrientedBox(r, b, sf::Transform::Identity) == true);
	}

	//IntersectOrientedBoxAlignedBox
	{
		AlignedBoxShape aar(sf::Vector2f(1.0f, 5.0f), sf::Vector2f(3.0f, 3.0f)); 
		OrientedBoxShape or(sf::Vector2f(10.0f, 4.0f), sf::Vector2f(4.0f, 2.0f), 25.0f); 
		
		assert(HasIntersectionOrientedBoxAlignedBox(or, sf::Transform::Identity, aar, sf::Transform::Identity) == false);
	}

	//FindIntersectionRayLineSegment
	{
		sf::Vector2f dir(1.0f,1.0f);
		dir = MathUtils::Normalize(dir);

		Ray r(sf::Vector2f(1.0f, 1.0f), dir);
		Ray r1(sf::Vector2f(4.0f, 2.0f), sf::Vector2f(0.0f, 1.0f));

		sf::Vector2f p0(0.0f, 1.0f);
		sf::Vector2f p1(1.0f, 0.0f);
		sf::Vector2f p2(1.0f, 3.0f);
		sf::Vector2f p3(1.0f, 4.0f);
		sf::Vector2f p4(3.0f, 1.0f);
		sf::Vector2f p5(3.0f, 4.0f);
		sf::Vector2f p6(5.0f, 4.0f);
		sf::Vector2f p7(4.0f, 4.0f);
		sf::Vector2f p8(4.0f, 5.0f);

		float param = 0.0f;
		int res = 0;

		res = FindIntersectionRayLineSegment(r, LineSegment(p0, p1), param);
		assert(res==0);

		res = FindIntersectionRayLineSegment(r, LineSegment(p0, p2), param);
		assert(res==0);

		res = FindIntersectionRayLineSegment(r, LineSegment(p2, p4), param);
		assert(res==1);

		res = FindIntersectionRayLineSegment(r, LineSegment(p3, p4), param);
		assert(res==1);

		res = FindIntersectionRayLineSegment(r1, LineSegment(p5, p6), param);
		assert(res==1);

		res = FindIntersectionRayLineSegment(r1, LineSegment(p7, p8), param);
		assert(res==2);
	}
}

}