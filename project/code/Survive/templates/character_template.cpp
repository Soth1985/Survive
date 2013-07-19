#include <Survive/templates/character_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(CharacterTemplate, SURVIVE_TYPELIST_1(Template))

Type* CharacterTemplate::GetType()const
{
	return TypeImpl<CharacterTemplate>::Instance();
}

}