#pragma once

#include <Survive/templates/weapon_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::RangedWeaponTemplate)

class RangedWeaponTemplate : public WeaponTemplate
{
public:

	virtual Type* GetType()const;
};

}