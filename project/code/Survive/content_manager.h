#pragma once

#include <Survive/content_holder.h>
#include <Survive/big_texture.h>

#include <SFML/Graphics/Texture.hpp>

namespace Survive
{

class ContentManager
{
public:

	typedef ContentHolder<BigTexture, eBigTextureID::Val> BigTexturesHolder;
	typedef ContentHolder<sf::Texture, eTextureID::Val> TexturesHolder;

	ContentManager();

	BigTexturesHolder& BigTextures()
	{
		return m_BigTextures;
	}

	TexturesHolder& Textures()
	{
		return m_Textures;
	}

	const std::string& GetContentMountPoint()const
	{
		return m_ContentMountPoint;
	}

	void SetContentMountPoint(const std::string& path)
	{
		m_ContentMountPoint = path;
	}

	BigTexture* LoadBigTexture(eBigTextureID::Val id, const std::string& path);

	sf::Texture* LoadTexture(eTextureID::Val id, const std::string& path);

private:

	BigTexturesHolder m_BigTextures;
	TexturesHolder m_Textures;
	std::string m_ContentMountPoint;
};

}