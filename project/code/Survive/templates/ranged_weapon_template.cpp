#include <Survive/templates/ranged_weapon_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(RangedWeaponTemplate, SURVIVE_TYPELIST_1(WeaponTemplate))

RangedWeaponTemplate::RangedWeaponTemplate()
	:
m_Damage(0),
m_ShootTime(FLT_MAX),
m_ProjectileSpeed(0.0f),
m_ProjectileTexId(eTextureID::TextureCount)
{
}

Type* RangedWeaponTemplate::GetType()const
{
	return TypeImpl<RangedWeaponTemplate>::Instance();
}

}