#include <Survive/templates/static_convex_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(StaticConvexTemplate, SURVIVE_TYPELIST_1(StaticObjectTemplate))

Type* StaticConvexTemplate::GetType()const
{
	return TypeImpl<StaticConvexTemplate>::Instance();
}

}