#include <Survive/templates/monster_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(MonsterTemplate, SURVIVE_TYPELIST_1(CharacterTemplate))

Type* MonsterTemplate::GetType()const
{
	return TypeImpl<MonsterTemplate>::Instance();
}

}