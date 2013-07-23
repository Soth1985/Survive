#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::WeaponTemplate)

class WeaponTemplate : public Template
{
public:

	virtual Type* GetType()const;
};

}