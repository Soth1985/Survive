#pragma once

#include <Survive/templates/template.h>
#include <Survive/templates/template_ref.h>
#include <Survive/templates/close_combat_weapon_template.h>
#include <Survive/templates/ranged_weapon_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CharacterTemplate)

class CharacterTemplate : public Template
{
public:

	CharacterTemplate();

	virtual Type* GetType()const;

	typedef std::pair<eTextureID::Val, float> TexIdPair;
	
	TemplateRef<RangedWeaponTemplate> m_RangedWeapon;
	TemplateRef<CloseCombatWeaponTemplate> m_CloseCombatWeapon;
	std::vector< TexIdPair > m_BodyTextures;
	int m_MaxHealth;
	float m_MoveSpeed;
};

}