#pragma once

#include <Survive/templates/weapon_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CloseCombatWeaponTemplate)

class CloseCombatWeaponTemplate : public WeaponTemplate
{
public:

	virtual Type* GetType()const;
};

}