#pragma once

#include <Survive/templates/weapon_template.h>

#include <SFML/System/Vector2.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CloseCombatWeaponTemplate)

class CloseCombatWeaponTemplate : public WeaponTemplate
{
public:

	CloseCombatWeaponTemplate();

	virtual Type* GetType()const;

	int m_Damage;
	float m_SwingTime;
	sf::Vector2f m_SwingSize;
};

}