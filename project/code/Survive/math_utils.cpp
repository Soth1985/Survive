#include <Survive/math_utils.h>
#include <time.h>

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

sf::Vector2f MathUtils::GetTranslation(const sf::Transform& Tf)
{
	const float* pMat = Tf.getMatrix();

	return sf::Vector2f(pMat[12], pMat[13]);
}

sf::Vector2f MathUtils::GetScale(const sf::Transform& Tf)
{
	const float* pMat = Tf.getMatrix();

	return sf::Vector2f(pMat[0], pMat[5]);
}

float MathUtils::GetRotation(const sf::Transform& Tf)
{
	sf::Vector2f Dir(1.0f, 0.0f);

	Tf.transformPoint(Dir);

	if (AreClose(Dir.x, 0.0f))
	{
		if (AreClose(Dir.y, 0.0f))
			return 0.0f;

		if (Dir.y > 0.0f)
			return 90.0f;
		else
			return -90.0f;
	}
	else
		return RadToDeg(atan2f(Dir.y, Dir.x));
}

bool MathUtils::IsIdentity(const sf::Transform& Tf)
{
	if (&Tf == &sf::Transform::Identity)
		return true;

	const float* IdnMtx = sf::Transform::Identity.getMatrix();
	const float* Mtx = Tf.getMatrix();

	for (size_t Idx = 0; Idx < 16; ++Idx)
	{
		if (IdnMtx[Idx] != Mtx[Idx])
			return false;
	}

	return true;
}

float MathUtils::RandomFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

float MathUtils::RandomRange(float Low, float High)
{
	float Res = (float)rand();
	Res /= RAND_MAX;
	Res = (High - Low) * Res + Low;
	return Res;
}

void MathUtils::RandomInit()
{
	time_t Seconds;
    time(&Seconds);
	srand((unsigned int)Seconds);
}

}