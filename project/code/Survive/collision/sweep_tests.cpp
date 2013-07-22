#include <Survive/collision/sweep_tests.h>
#include <Survive/collision/intersection_tests.h>
#include <Survive/math_utils.h>

namespace Survive
{

static bool NoIntersect(float Tmax, float Speed, const Range& R0, const Range& R1, float& Tfirst, float& Tlast)
{
	if (R1.GetMax() < R0.GetMin()) 
	{
		if (Speed <= 0) 
			return true;

		float t = (R0.GetMin() - R1.GetMax()) / Speed; 

		if (t > Tfirst) 
			Tfirst = t;

		if (Tfirst > Tmax) 
			return true;

		t = (R0.GetMax() - R1.GetMin()) /Speed; 

		if (t < Tlast) 
			Tlast = t;

		if (Tfirst > Tlast)
			return true;
	} 
	else if (R0.GetMax() < R1.GetMin())
	{
		if (Speed >= 0) 
			return true;

		float t = (R0.GetMax() - R1.GetMin())/Speed; 

		if ( t > Tfirst ) 
			Tfirst = t;

		if (Tfirst > Tmax) 
			return true;

		t = (R0.GetMin() - R1.GetMax())/Speed; 

		if ( t < Tlast ) 
			Tlast = t;

		if (Tfirst > Tlast)
			return true;
	} 
	else
	{
		if (Speed > 0) 
		{
			float t = (R0.GetMax() - R1.GetMin()) / Speed;

			if (t < Tlast)
				Tlast = t;

			if (Tfirst > Tlast)
				return true;

		} 
		else if (Speed < 0)
		{
			float t = (R0.GetMin() - R1.GetMax()) / Speed;

			if (t < Tlast) 
				Tlast = t;

			if (Tfirst > Tlast) 
				return true;
		}
	}

	return false;
}

int SweepTests::SweepConvexPolygonConvexPolygon(const ConvexPolygonShape& InP1, const sf::Transform& P1Tf, const ConvexPolygonShape& InP2, const sf::Transform& P2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	ConvexPolygonShape P1(InP1);
	P1.TransformShape(P1Tf);

	ConvexPolygonShape P2(InP2);
	P2.TransformShape(P2Tf);

	sf::Vector2f RelVel = V2 - V1;
	Tfirst = 0;
	Tlast = FLT_MAX;

	for (size_t Idx0 = 0, Idx1 = P1.GetPointC() - 1; Idx0 < P1.GetPointC(); Idx1 = Idx0, ++Idx0) 
	{
		sf::Vector2f Edge = P1[Idx0] - P1[Idx1];
		sf::Vector2f D = MathUtils::GetVectorNormal(Edge);
		Range R1 = IntersectionTests::ComputeInterval(P1, D);
		Range R2 = IntersectionTests::ComputeInterval(P2, D);
		
		float Speed = MathUtils::DotProduct(D, RelVel);
		if (NoIntersect(Tmax, Speed, R1, R2, Tfirst, Tlast))
			return false;
	}

	for (size_t Idx0 = 0, Idx1 = P2.GetPointC() - 1; Idx0 < P2.GetPointC(); Idx1 = Idx0, ++Idx0)
	{
		sf::Vector2f Edge = P2[Idx0] - P2[Idx1];
		sf::Vector2f D = MathUtils::GetVectorNormal(Edge);
		Range R1 = IntersectionTests::ComputeInterval(P1, D);
		Range R2 = IntersectionTests::ComputeInterval(P2, D);

		float Speed = MathUtils::DotProduct(D, RelVel);
		if (NoIntersect(Tmax, Speed, R1, R2, Tfirst, Tlast))
			return false;
	}

	return true;
}

int SweepTests::SweepAlignedBoxConvexPolygon(const AlignedBoxShape& InBox, const sf::Transform& BoxTf, const ConvexPolygonShape& InP, const sf::Transform& PTf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	ConvexPolygonShape TempShape(4);
	InBox.ToConvex(&TempShape);

	return SweepConvexPolygonConvexPolygon(TempShape, BoxTf, InP, PTf, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepOrientedBoxConvexPolygon(const OrientedBoxShape& InBox, const sf::Transform& BoxTf, const ConvexPolygonShape& InP, const sf::Transform& PTf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	ConvexPolygonShape TempShape(4);
	InBox.ToConvex(&TempShape);

	return SweepConvexPolygonConvexPolygon(TempShape, BoxTf, InP, PTf, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepOrientedBoxOrientedBox(const OrientedBoxShape& InBox1, const sf::Transform& Box1Tf, const OrientedBoxShape& InBox2, const sf::Transform& Box2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	ConvexPolygonShape TempShape1(4);
	ConvexPolygonShape TempShape2(4);

	InBox1.ToConvex(&TempShape1);
	InBox2.ToConvex(&TempShape2);

	return SweepConvexPolygonConvexPolygon(TempShape1, Box1Tf, TempShape2, Box2Tf, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepAlignedBoxAlignedBox(const AlignedBoxShape& InBox1, const sf::Transform& Box1Tf, const AlignedBoxShape& InBox2, const sf::Transform& Box2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	ConvexPolygonShape TempShape1(4);
	ConvexPolygonShape TempShape2(4);

	InBox1.ToConvex(&TempShape1);
	InBox2.ToConvex(&TempShape2);

	return SweepConvexPolygonConvexPolygon(TempShape1, Box1Tf, TempShape2, Box2Tf, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepAlignedBoxOrientedBox(const AlignedBoxShape& InBox1, const sf::Transform& Box1Tf, const OrientedBoxShape& InBox2, const sf::Transform& Box2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	ConvexPolygonShape TempShape1(4);
	ConvexPolygonShape TempShape2(4);

	InBox1.ToConvex(&TempShape1);
	InBox2.ToConvex(&TempShape2);

	return SweepConvexPolygonConvexPolygon(TempShape1, Box1Tf, TempShape2, Box2Tf, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepShapeShape(const CollisionShape& Shape1, const sf::Transform& Shape1Tf, const CollisionShape& Shape2, const sf::Transform& Shape2Tf, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	const AlignedBoxShape* Aligned1 = TypeCast<AlignedBoxShape>(&Shape1);

	if (Aligned1)
	{
		const AlignedBoxShape* Aligned2 = TypeCast<AlignedBoxShape>(&Shape2);

		if (Aligned2)
			return SweepAlignedBoxAlignedBox(*Aligned1, Shape1Tf, *Aligned2, Shape2Tf, V1, V2, Tmax, Tfirst, Tlast);

		const ConvexPolygonShape* Convex2 = TypeCast<ConvexPolygonShape>(&Shape2);

		if (Convex2)
			return SweepAlignedBoxConvexPolygon(*Aligned1, Shape1Tf, *Convex2, Shape2Tf, V1, V2, Tmax, Tfirst, Tlast);

		const OrientedBoxShape* Oriented2 = TypeCast<OrientedBoxShape>(&Shape2);

		if (Oriented2)
			return SweepAlignedBoxOrientedBox(*Aligned1, Shape1Tf, *Oriented2, Shape2Tf, V1, V2, Tmax, Tfirst, Tlast); 
	}

	const ConvexPolygonShape* Convex1 = TypeCast<ConvexPolygonShape>(&Shape1);

	if (Convex1)
	{
		const AlignedBoxShape* Aligned2 = TypeCast<AlignedBoxShape>(&Shape2);

		if (Aligned2)
			return SweepAlignedBoxConvexPolygon(*Aligned2, Shape2Tf, *Convex1, Shape1Tf, V1, V2, Tmax, Tfirst, Tlast);

		const ConvexPolygonShape* Convex2 = TypeCast<ConvexPolygonShape>(&Shape2);

		if (Convex2)
			return SweepConvexPolygonConvexPolygon(*Convex1, Shape1Tf, *Convex2, Shape2Tf, V1, V2, Tmax, Tfirst, Tlast);

		const OrientedBoxShape* Oriented2 = TypeCast<OrientedBoxShape>(&Shape2);

		if (Oriented2)
			return SweepOrientedBoxConvexPolygon(*Oriented2, Shape2Tf, *Convex1, Shape1Tf, V1, V2, Tmax, Tfirst, Tlast);
	}

	const OrientedBoxShape* Oriented1 = TypeCast<OrientedBoxShape>(&Shape1);

	if (Oriented1)
	{
		const AlignedBoxShape* Aligned2 = TypeCast<AlignedBoxShape>(&Shape2);

		if (Aligned2)
			return SweepAlignedBoxOrientedBox(*Aligned2, Shape2Tf, *Oriented1, Shape1Tf, V1, V2, Tmax, Tfirst, Tlast);

		const ConvexPolygonShape* Convex2 = TypeCast<ConvexPolygonShape>(&Shape2);

		if (Convex2)
			return SweepOrientedBoxConvexPolygon(*Oriented1, Shape1Tf, *Convex2, Shape2Tf, V1, V2, Tmax, Tfirst, Tlast);

		const OrientedBoxShape* Oriented2 = TypeCast<OrientedBoxShape>(&Shape2);

		if (Oriented2)
			return SweepOrientedBoxOrientedBox(*Oriented1, Shape1Tf, *Oriented2, Shape2Tf, V1, V2, Tmax, Tfirst, Tlast); 
	}

	return false;
}

}