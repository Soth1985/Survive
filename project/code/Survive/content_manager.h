#pragma once

#include <Survive/content_holder.h>
#include <Survive/big_texture.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Survive
{

class ContentManager
{
public:

	typedef ContentHolder<BigTexture, eBigTextureID::Val> BigTexturesHolder;
	typedef ContentHolder<sf::Texture, eTextureID::Val> TexturesHolder;
	typedef ContentHolder<sf::Font, eFontID::Val> FontsHolder;

	ContentManager();

	const BigTexturesHolder& BigTextures()const
	{
		return m_BigTextures;
	}

	const TexturesHolder& Textures()const
	{
		return m_Textures;
	}

	const FontsHolder& Fonts()const
	{
		return m_Fonts;
	}

	const std::string& GetContentMountPoint()const
	{
		return m_ContentMountPoint;
	}

	void SetContentMountPoint(const std::string& path)
	{
		m_ContentMountPoint = path;
	}

	BigTexture* LoadBigTexture(eBigTextureID::Val Id);

	sf::Texture* LoadTexture(eTextureID::Val Id);

	sf::Font* LoadFont(eFontID::Val Id);

private:

	BigTexturesHolder m_BigTextures;
	TexturesHolder m_Textures;
	FontsHolder m_Fonts;
	std::string m_ContentMountPoint;
};

}