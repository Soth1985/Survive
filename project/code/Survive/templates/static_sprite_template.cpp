#include <Survive/templates/static_sprite_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(StaticSpriteTemplate, SURVIVE_TYPELIST_1(StaticObjectTemplate))

Type* StaticSpriteTemplate::GetType()const
{
	return TypeImpl<StaticSpriteTemplate>::Instance();
}

}