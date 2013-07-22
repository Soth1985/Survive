#pragma once

#include <Survive/forward.h>
#include <Survive/rtti.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CollisionShape);

class CollisionShape: public Rtti
{
public:

	CollisionShape();

	virtual Type* GetType()const;

	virtual void GetAlignedHull(AlignedBoxShape* pHull)const = 0;

	virtual bool Contains(const sf::Vector2f& Point)const = 0;

	virtual bool Contains(const sf::Vector2f& Point, const sf::Transform& Tf)const = 0;

	virtual eCollisionShapeKind::Val GetShapeKind()const = 0;

	virtual void TransformShape(const sf::Transform& Tf) = 0;

	virtual sf::Vector2f GetShapeCenter()const = 0;

	int GetCollisionGroup()const
	{
		return m_CollisionGroup;
	}

	void SetCollisionGroup(int Group)
	{
		m_CollisionGroup = Group;
	}

private:

	int m_CollisionGroup;
};

}