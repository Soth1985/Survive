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

BigTexture* ContentManager::LoadBigTexture(eBigTextureID::Val id)
{
	BigTexture* result = new BigTexture();

	ContentTemplate* Content = TemplateManager::Instance().GetTemplate<ContentTemplate>("Content");

	std::string realPath = m_ContentMountPoint + Content->m_BigTextures[id];

	if (!result->LoadFromFile(realPath))
	{
		delete result;
		return 0;
	}

	m_BigTextures.Set(id, result);

	return result;
}

sf::Texture* ContentManager::LoadTexture(eTextureID::Val id)
{
	sf::Texture* result = new sf::Texture();

	ContentTemplate* Content = TemplateManager::Instance().GetTemplate<ContentTemplate>("Content");

	std::string realPath = m_ContentMountPoint + Content->m_Textures[id];

	if (!result->loadFromFile(realPath))
	{
		delete result;
		return 0;
	}

	m_Textures.Set(id, result);

	return result;
}

}