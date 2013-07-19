#pragma once

#include <Survive/templates/character_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PlayerTemplate)

class PlayerTemplate : public CharacterTemplate
{
public:

	virtual Type* GetType()const;
};

}