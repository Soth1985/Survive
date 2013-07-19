#pragma once

#include <Survive/forward.h>
#include <Survive/rtti.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::Template);

class Template: public Rtti
{
public:

	virtual Type* GetType()const;
};

}