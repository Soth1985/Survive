#include <Survive/templates/static_object_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(StaticObjectTemplate, SURVIVE_TYPELIST_1(Template))

Type* StaticObjectTemplate::GetType()const
{
	return TypeImpl<StaticObjectTemplate>::Instance();
}

}