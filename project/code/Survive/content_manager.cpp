#include <Survive/content_manager.h>
#include <Survive/templates/template_manager.h>
#include <Survive/templates/content_template.h>

namespace Survive
{

ContentManager::ContentManager()
	:
m_ContentMountPoint("../../../../content/")
{

}

BigTexture* ContentManager::LoadBigTexture(eBigTextureID::Val Id)
{
	BigTexture* Result = new BigTexture();

	ContentTemplate* Content = TemplateManager::Instance().GetTemplate<ContentTemplate>("Content");

	std::string RealPath = m_ContentMountPoint + Content->m_BigTextures[Id];

	if (!Result->LoadFromFile(RealPath))
	{
		assert(0);
		delete Result;
		return 0;
	}

	m_BigTextures.Set(Id, Result);

	return Result;
}

sf::Texture* ContentManager::LoadTexture(eTextureID::Val Id)
{
	sf::Texture* Result = new sf::Texture();

	ContentTemplate* Content = TemplateManager::Instance().GetTemplate<ContentTemplate>("Content");

	std::string RealPath = m_ContentMountPoint + Content->m_Textures[Id];

	if (!Result->loadFromFile(RealPath))
	{
		assert(0);
		delete Result;
		return 0;
	}

	m_Textures.Set(Id, Result);

	return Result;
}

sf::Font* ContentManager::LoadFont(eFontID::Val Id)
{
	sf::Font* Result = new sf::Font();

	ContentTemplate* Content = TemplateManager::Instance().GetTemplate<ContentTemplate>("Content");

	std::string RealPath = m_ContentMountPoint + Content->m_Fonts[Id];

	if (!Result->loadFromFile(RealPath))
	{
		assert(0);
		delete Result;
		return 0;
	}

	m_Fonts.Set(Id, Result);

	return Result;
}

}