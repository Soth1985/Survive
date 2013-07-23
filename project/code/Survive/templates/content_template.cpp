#include <Survive/templates/content_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(ContentTemplate, SURVIVE_TYPELIST_1(Template))

ContentTemplate::ContentTemplate()
{
}

Type* ContentTemplate::GetType()const
{
	return TypeImpl<ContentTemplate>::Instance();
}

}