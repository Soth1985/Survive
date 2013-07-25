#include <Survive/templates/pickup_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(PickupTemplate, SURVIVE_TYPELIST_1(Template))

PickupTemplate::PickupTemplate()
	:
m_TexId(eTextureID::TextureCount),
m_HealthToGive(0)
{

}

Type* PickupTemplate::GetType()const
{
	return TypeImpl<PickupTemplate>::Instance();
}

}