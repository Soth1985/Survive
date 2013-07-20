#pragma once

#include <Survive/forward.h>
#include <Survive/rtti.h>

#include <SFML/System/Vector2.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CollisionShape);

class CollisionShape: public Rtti
{
public:

	virtual Type* GetType()const;
};

}