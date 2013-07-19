#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CharacterTemplate)

class CharacterTemplate : public Template
{
public:

	virtual Type* GetType()const;
};

}