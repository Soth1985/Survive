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
private:

	sf::Sprite m_Body;
	sf::Sprite m_RangedWeapon;
	sf::Sprite m_CloseCombatWeapon;
};

}