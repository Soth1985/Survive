#include <Survive/templates/player_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(PlayerTemplate, SURVIVE_TYPELIST_1(CharacterTemplate))

Type* PlayerTemplate::GetType()const
{
	return TypeImpl<PlayerTemplate>::Instance();
}

}