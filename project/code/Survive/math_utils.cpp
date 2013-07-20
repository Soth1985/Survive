#include <Survive/math_utils.h>

namespace Survive
{

const float MathUtils::Pi = 3.14159265358979323846f;

sf::Vector2f MathUtils::GetVectorNormal(const sf::Vector2f& Vector)
{
	sf::Vector2f Result;

	Result.x = -Vector.y;
	Result.y = Vector.x; 
	return Result;
}

bool MathUtils::AreParallel(const sf::Vector2f& V1, const sf::Vector2f& V2)
{
	sf::Vector2f N1 = GetVectorNormal(V1);

	return AreClose(DotProduct(N1, V2), 0.0f);
}

float MathUtils::DotProduct(const sf::Vector2f& V1, const sf::Vector2f& V2)
{
	return V1.x * V2.x + V1.y * V2.y;
}

bool MathUtils::AreClose(float A, float B)
{
	static const float Epsilon = 0.001f;

	return fabsf(A - B) < Epsilon;
}

bool MathUtils::AreClose(const sf::Vector2f& A, const sf::Vector2f& B)
{
	return AreClose(A.x - B.x, 0.0f) && AreClose(A.y - B.y, 0.0f);
}

sf::Vector2f MathUtils::Normalize(const sf::Vector2f& A)
{
	float Len = Length(A);

	sf::Vector2f result(A);

	result *= (1.0f / Len);

	return result;
}

float MathUtils::Length(const sf::Vector2f& A)
{
	float Dot = DotProduct(A, A);

	return sqrtf(Dot);
}

sf::Vector2f MathUtils::ProjectVector(const sf::Vector2f& A, const sf::Vector2f& Dir)
{
	sf::Vector2f Result(Dir);

	float Dot = DotProduct(Dir, Dir);

	if(0 != Dot)
		Result = Dir * (DotProduct(A, Dir) / Dot);

	return Result;
}

sf::Vector2f MathUtils::RotateVector(const sf::Vector2f& A, float AngleDegrees)
{
	float Radian = DegToRad(AngleDegrees);
	float Sine = sinf(Radian);
	float Cosine = cosf(Radian);

	return sf::Vector2f(A.x * Cosine - A.y * Sine, A.x * Sine + A.y * Cosine);
}

float MathUtils::DegToRad(float Deg)
{
	return Deg * Pi / 180.0f;
}

float MathUtils::RadToDeg(float Rad)
{
	return Rad * 180.0f / Pi;
}

}