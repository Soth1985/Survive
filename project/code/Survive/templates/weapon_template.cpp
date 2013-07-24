#include <Survive/templates/weapon_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(WeaponTemplate, SURVIVE_TYPELIST_1(Template))

WeaponTemplate::WeaponTemplate()
	:
m_Texture(eTextureID::TextureCount)
{
}

Type* WeaponTemplate::GetType()const
{
	return TypeImpl<WeaponTemplate>::Instance();
}

}