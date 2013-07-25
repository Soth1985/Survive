#pragma once

#include <Survive/templates/character_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::MonsterTemplate)

class MonsterTemplate : public CharacterTemplate
{
public:

	MonsterTemplate();

	virtual Type* GetType()const;

	float m_DropChance;
};

}