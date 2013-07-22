#include <Survive/templates/content_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(ContentTemplate, SURVIVE_TYPELIST_1(Template))

ContentTemplate::ContentTemplate()
{
	m_BigTextures[eBigTextureID::Landscape] = "Textures/grass_map_150.jpg";
	m_Textures[eTextureID::MainMenuBackground] = "Textures/main_menu_background.jpg";
	m_Textures[eTextureID::ChaosLordBody] = "Textures/chaos_lord/chaos_lord_body.png";
	m_Textures[eTextureID::ChaosLordBolter] = "Textures/chaos_lord/chaos_lord_bolter.png";
	m_Textures[eTextureID::ChaosLordPlasma] = "Textures/chaos_lord/chaos_lord_plasma.png";
	m_Textures[eTextureID::ChaosLordMelta] = "Textures/chaos_lord/chaos_lord_melta.png";
	m_Textures[eTextureID::ChaosLordSword] = "Textures/chaos_lord/chaos_lord_sword.png";

	m_Fonts[eFontID::Arial] = "Fonts/arial.ttf";
}

Type* ContentTemplate::GetType()const
{
	return TypeImpl<ContentTemplate>::Instance();
}

}