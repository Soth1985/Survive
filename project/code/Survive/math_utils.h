#pragma once

#include <Survive/forward.h>

#include <SFML/System/Vector2.hpp>

namespace Survive
{

class MathUtils
{
public:

	static const float Pi;

	static sf::Vector2f GetVectorNormal(const sf::Vector2f& Vector);

	static bool AreParallel(const sf::Vector2f& V1, const sf::Vector2f& V2);

	static float DotProduct(const sf::Vector2f& V1, const sf::Vector2f& V2);

	static bool AreClose(float A, float B);

	static bool AreClose(const sf::Vector2f& A, const sf::Vector2f& B);

	static sf::Vector2f Normalize(const sf::Vector2f& A);

	static float Length(const sf::Vector2f& A);

	static sf::Vector2f ProjectVector(const sf::Vector2f& A, const sf::Vector2f& Dir);

	static sf::Vector2f RotateVector(const sf::Vector2f& A, float AngleDegrees);

	static float DegToRad(float Deg);

	static float RadToDeg(float Rad);
};

}