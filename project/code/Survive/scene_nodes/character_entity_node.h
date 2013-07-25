#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/dynamic_entity_node.h>

#include <SFML/Graphics/Sprite.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CharacterEntityNode);

class CharacterEntityNode : public DynamicEntityNode
{
public:

	CharacterEntityNode();

	virtual void InitFromTemplate(const Template* Tmpl);

	virtual Type* GetType()const;

	virtual AlignedBoxShape GetBounds();

	virtual const CollisionShape* GetCollisionShape()const;

	virtual void OnHit(int Damage);

	virtual unsigned int GetBulletTraceMask()const = 0;

	void UseRangedWeapon(const sf::Vector2f& ShootDir);

	void UseCloseCombatWeapon(unsigned int CollisionMask);

	float GetSpeed()const;

	int GetHealth()const;

	int GetMaxHealth()const;

protected:

	void AddHealth(int Health);

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	sf::Sprite m_Body;	
	AlignedBoxShape m_Collision;
	int m_Health;

	const CharacterTemplate* m_pCharacterTmpl;

	const RangedWeaponTemplate* m_pRangedWeaponTmpl;
	sf::Sprite m_RangedWeaponSprite;
	float m_RangedWeaponUseTimer;

	const CloseCombatWeaponTemplate* m_pCloseCombatWeaponTmpl;
	sf::Sprite m_CloseCombatSprite;
	float m_CloseCombatWeaponUseTime;

	const WeaponTemplate* m_pLastWeaponTmpl;
};

}