#include <Survive/big_texture.h>

#include <SFML/Graphics/Sprite.hpp>

namespace Survive
{

struct Utils
{
	template <typename T>
	static T& map(std::vector<T>& vector, unsigned int x, unsigned int y, sf::Vector2u tableSize)
	{
		return vector[y * tableSize.x + x];
	}

	template <typename T>
	static const T& map(const std::vector<T>& vector, unsigned int x, unsigned int y, sf::Vector2u tableSize)
	{
		return vector[y * tableSize.x + x];
	}
};

BigTexture::BigTexture()
	:
m_TableSize(0u, 0u),
m_PixelSize(0u, 0u),
m_Smooth(false)
{
	m_MaxSize = std::min(2048u, sf::Texture::getMaximumSize());
}

void BigTexture::Swap(BigTexture& Other)
{
	std::swap(m_Textures,  Other.m_Textures);
	std::swap(m_TableSize, Other.m_TableSize);
	std::swap(m_PixelSize, Other.m_PixelSize);
	std::swap(m_Smooth,    Other.m_Smooth);
}

bool BigTexture::LoadFromImage(const sf::Image& Source)
{
	BigTexture Tmp;
	
	Tmp.m_PixelSize = Source.getSize();

	Tmp.m_TableSize.x = (Tmp.m_PixelSize.x - 1u) / m_MaxSize + 1u;
	Tmp.m_TableSize.y = (Tmp.m_PixelSize.y - 1u) / m_MaxSize + 1u;

	Tmp.m_Textures.reserve(Tmp.m_TableSize.x * Tmp.m_TableSize.y);

	for (unsigned int yI = 0u; yI < Tmp.m_PixelSize.y; yI += m_MaxSize) 
	{
		for (unsigned int xI = 0u; xI < Tmp.m_PixelSize.x; xI += m_MaxSize) 
		{ 
			Tmp.m_Textures.push_back(sf::Texture()); 
			if (!Tmp.m_Textures.back().loadFromImage(Source, sf::IntRect(xI, yI, m_MaxSize, m_MaxSize)))
				return false;
		}
	}

	Tmp.SetSmooth(IsSmooth());

	Swap(Tmp);
	return true;
}

bool BigTexture::LoadFromFile(const std::string& Filename)
{
	sf::Image Image;
	return Image.loadFromFile(Filename) && LoadFromImage(Image);
}

bool BigTexture::LoadFromMemory(const void* Data, size_t Size)
{
	sf::Image Image;
	return Image.loadFromMemory(Data, Size) && LoadFromImage(Image);
}

bool BigTexture::LoadFromStream(sf::InputStream& Stream)
{
	sf::Image Image;
	return Image.loadFromStream(Stream) && LoadFromImage(Image);
}

sf::Vector2u BigTexture::GetSize() const
{
	return m_PixelSize;
}

void BigTexture::SetSmooth(bool Smooth)
{
	if (m_Smooth != Smooth)
	{
		m_Smooth = Smooth;

		for (size_t Idx = 0; Idx < m_Textures.size(); ++Idx)
		{
			m_Textures[Idx].setSmooth(Smooth);
		}
	}
}

bool BigTexture::IsSmooth()const
{
	return m_Smooth;
}

sf::Vector2f BigTexture::FillSprites(const sf::Color& Color, std::vector<sf::Sprite>& Out) const
{
	Out.clear();
	Out.resize(m_Textures.size());

	for (unsigned int i = 0u; i < m_TableSize.x; ++i)
	{
		for (unsigned int j = 0u; j < m_TableSize.y; ++j)
		{
			const sf::Texture& Texture = Utils::map(m_Textures, i, j, m_TableSize);
			sf::Sprite&	       Sprite  = Utils::map(Out,       i, j, m_TableSize);

			Sprite.setColor(Color);
			Sprite.setTexture(Texture);
			Sprite.setPosition(static_cast<float>(i * m_MaxSize), static_cast<float>(j * m_MaxSize));
		}
	}

	return sf::Vector2f(m_PixelSize);
}

}