#pragma once

#include <Survive/forward.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

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

	static sf::Vector2f GetTranslation(const sf::Transform& Tf);

	static sf::Vector2f GetScale(const sf::Transform& Tf);

	static float GetRotation(const sf::Transform& Tf);

	static bool IsIdentity(const sf::Transform& Tf);

	static void RandomInit();

	static float RandomRange(float Low, float High);

	static float RandomFloat();

	template <class T>
	static const T& GetRandomItem(const std::vector< std::pair<T, float> >& Items)
	{
		float TotalWeight = 0.0f;

		for (size_t Idx = 0; Idx < Items.size(); ++Idx)
		{
			TotalWeight += Items[Idx].second;
		}

		assert(Items.size() > 0 && TotalWeight > 0.0f);

		TotalWeight = 1.0f / TotalWeight;

		float Rnd = RandomFloat();

		float CurWeight = 0.0f;

		for (size_t Idx = 0; Idx < Items.size(); ++Idx)
		{
			CurWeight += Items[Idx].second * TotalWeight;

			if (Rnd < CurWeight)
			{
				return Items[Idx].first;
			}
		}

		assert(0);

		return Items[0].first;
	}
};

}