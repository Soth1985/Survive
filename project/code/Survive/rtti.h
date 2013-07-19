#pragma once

#include <Survive/forward.h>
#include <Survive/type_info.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::Rtti);

class Rtti
{
public:

	virtual ~Rtti();

	virtual Type* GetType()const = 0;
};

}