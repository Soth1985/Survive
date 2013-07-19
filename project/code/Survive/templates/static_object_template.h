#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::StaticObjectTemplate)

class StaticObjectTemplate : public Template
{
public:

	virtual Type* GetType()const;
};

}