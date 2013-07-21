#include <Survive/collision/sweep_tests.h>
#include <Survive/collision/intersection_tests.h>
#include <Survive/math_utils.h>

namespace Survive
{

ConvexPolygonShape SweepTests::m_TempShape1(4);
ConvexPolygonShape SweepTests::m_TempShape2(4);

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

int SweepTests::SweepConvexPolygonConvexPolygon(const ConvexPolygonShape& P1, const ConvexPolygonShape& P2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
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

int SweepTests::SweepAlignedBoxConvexPolygon(const AlignedBoxShape& Box, const ConvexPolygonShape& P, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	m_TempShape1[0] = Box.GetCorner(0);
	m_TempShape1[1] = Box.GetCorner(1);
	m_TempShape1[2] = Box.GetCorner(2);
	m_TempShape1[3] = Box.GetCorner(3);

	return SweepConvexPolygonConvexPolygon(m_TempShape1, P, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepOrientedBoxConvexPolygon(const OrientedBoxShape& Box, const ConvexPolygonShape& P, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	m_TempShape1[0] = Box.GetCorner(0);
	m_TempShape1[1] = Box.GetCorner(1);
	m_TempShape1[2] = Box.GetCorner(2);
	m_TempShape1[3] = Box.GetCorner(3);

	return SweepConvexPolygonConvexPolygon(m_TempShape1, P, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepOrientedBoxOrientedBox(const OrientedBoxShape& Box1, const OrientedBoxShape& Box2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	m_TempShape1[0] = Box1.GetCorner(0);
	m_TempShape1[1] = Box1.GetCorner(1);
	m_TempShape1[2] = Box1.GetCorner(2);
	m_TempShape1[3] = Box1.GetCorner(3);

	m_TempShape2[0] = Box2.GetCorner(0);
	m_TempShape2[1] = Box2.GetCorner(1);
	m_TempShape2[2] = Box2.GetCorner(2);
	m_TempShape2[3] = Box2.GetCorner(3);

	return SweepConvexPolygonConvexPolygon(m_TempShape1, m_TempShape2, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepAlignedBoxAlignedBox(const AlignedBoxShape& Box1, const AlignedBoxShape& Box2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	m_TempShape1[0] = Box1.GetCorner(0);
	m_TempShape1[1] = Box1.GetCorner(1);
	m_TempShape1[2] = Box1.GetCorner(2);
	m_TempShape1[3] = Box1.GetCorner(3);

	m_TempShape2[0] = Box2.GetCorner(0);
	m_TempShape2[1] = Box2.GetCorner(1);
	m_TempShape2[2] = Box2.GetCorner(2);
	m_TempShape2[3] = Box2.GetCorner(3);

	return SweepConvexPolygonConvexPolygon(m_TempShape1, m_TempShape2, V1, V2, Tmax, Tfirst, Tlast);
}

int SweepTests::SweepAlignedBoxOrientedBox(const AlignedBoxShape& Box1, const OrientedBoxShape& Box2, const sf::Vector2f& V1, const sf::Vector2f& V2, float Tmax, float& Tfirst, float& Tlast)
{
	m_TempShape1[0] = Box1.GetCorner(0);
	m_TempShape1[1] = Box1.GetCorner(1);
	m_TempShape1[2] = Box1.GetCorner(2);
	m_TempShape1[3] = Box1.GetCorner(3);

	m_TempShape2[0] = Box2.GetCorner(0);
	m_TempShape2[1] = Box2.GetCorner(1);
	m_TempShape2[2] = Box2.GetCorner(2);
	m_TempShape2[3] = Box2.GetCorner(3);

	return SweepConvexPolygonConvexPolygon(m_TempShape1, m_TempShape2, V1, V2, Tmax, Tfirst, Tlast);
}

}