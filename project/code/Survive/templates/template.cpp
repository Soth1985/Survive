#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_REG_TYPE(Template, SURVIVE_TYPELIST_1(Rtti))

Type* Template::GetType()const
{
	return TypeImpl<Template>::Instance();
}

}