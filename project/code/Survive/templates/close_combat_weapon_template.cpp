#include <Survive/templates/close_combat_weapon_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(CloseCombatWeaponTemplate, SURVIVE_TYPELIST_1(WeaponTemplate))

CloseCombatWeaponTemplate::CloseCombatWeaponTemplate()
	:
m_Damage(0),
m_SwingTime(FLT_MAX),
m_SwingSize(30.0f, 50.0f)
{
}

Type* CloseCombatWeaponTemplate::GetType()const
{
	return TypeImpl<CloseCombatWeaponTemplate>::Instance();
}

}