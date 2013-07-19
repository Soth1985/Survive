#include <Survive/templates/content_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(ContentTemplate, SURVIVE_TYPELIST_1(Template))

ContentTemplate::ContentTemplate()
{
	m_BigTextures[eBigTextureID::Landscape] = "Textures/grass_map_150.jpg";
	m_Textures[eTextureID::MainMenuBackground] = "Textures/main_menu_background.jpg";
}

Type* ContentTemplate::GetType()const
{
	return TypeImpl<ContentTemplate>::Instance();
}

}