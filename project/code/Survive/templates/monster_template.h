#pragma once

#include <Survive/templates/character_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::MonsterTemplate)

class MonsterTemplate : public CharacterTemplate
{
public:

	virtual Type* GetType()const;
};

}