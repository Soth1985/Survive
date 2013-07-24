#include <Survive/templates/character_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(CharacterTemplate, SURVIVE_TYPELIST_1(Template))

CharacterTemplate::CharacterTemplate()
	:
m_MaxHealth(100),
m_MoveSpeed(100.0f)
{
	
}

Type* CharacterTemplate::GetType()const
{
	return TypeImpl<CharacterTemplate>::Instance();
}

}