#pragma once

#include <Survive/forward.h>
#include <SFML/Graphics/Texture.hpp>

namespace Survive
{

class BigTexture
{
public:
		
	BigTexture();

	void Swap(BigTexture& Other);

	bool LoadFromImage(const sf::Image& Image);

	bool LoadFromFile(const std::string& Filename);

	bool LoadFromMemory(const void* Data, std::size_t Size);

	bool LoadFromStream(sf::InputStream& Stream);

	sf::Vector2u GetSize()const;

	void SetSmooth(bool Smooth);

	bool IsSmooth()const;

private:
		
	sf::Vector2f FillSprites(const sf::Color& Color, std::vector<sf::Sprite>& Out) const;
	
	std::vector<sf::Texture>	m_Textures;
	sf::Vector2u				m_TableSize;
	sf::Vector2u				m_PixelSize;
	bool						m_Smooth;
	unsigned int				m_MaxSize;

	friend class BigSprite;
};

}
