#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PickupTemplate)

class PickupTemplate : public Template
{
public:

	virtual Type* GetType()const;
};

}