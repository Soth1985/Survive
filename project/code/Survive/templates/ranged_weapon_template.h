#pragma once

#include <Survive/templates/weapon_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::RangedWeaponTemplate)

class RangedWeaponTemplate : public WeaponTemplate
{
public:

	RangedWeaponTemplate();

	virtual Type* GetType()const;

	int m_Damage;
	float m_ShootTime;
	float m_ProjectileSpeed;
	eTextureID::Val m_ProjectileTexId;	
};

}