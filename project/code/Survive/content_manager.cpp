#include <Survive/content_manager.h>

namespace Survive
{

ContentManager::ContentManager()
	:
m_ContentMountPoint("../../../../content/")
{

}

BigTexture* ContentManager::LoadBigTexture(eBigTextureID::Val id, const std::string& path)
{
	BigTexture* result = new BigTexture();

	std::string realPath = m_ContentMountPoint + path;

	if (!result->LoadFromFile(realPath))
	{
		delete result;
		return 0;
	}

	m_BigTextures.Set(id, result);

	return result;
}

sf::Texture* ContentManager::LoadTexture(eTextureID::Val id, const std::string& path)
{
	sf::Texture* result = new sf::Texture();

	std::string realPath = m_ContentMountPoint + path;

	if (!result->loadFromFile(realPath))
	{
		delete result;
		return 0;
	}

	m_Textures.Set(id, result);

	return result;
}

}