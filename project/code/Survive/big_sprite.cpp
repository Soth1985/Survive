#include <Survive/big_sprite.h>
#include <Survive/big_texture.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Survive
{
	
BigSprite::BigSprite()
	: 
sf::Drawable(),
sf::Transformable(),
m_Size(0.f, 0.f),
m_SplitSprites(),
m_Color(sf::Color::White)
{
}

BigSprite::BigSprite(const BigTexture& Texture)
	: 
sf::Drawable(),
sf::Transformable(),
m_Size(),
m_SplitSprites(),
m_Color(sf::Color::White)
{
	SetTexture(Texture);
}

void BigSprite::SetTexture(const BigTexture& Texture)
{
	m_Size = Texture.FillSprites(m_Color, m_SplitSprites);
}

void BigSprite::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	States.transform *= getTransform();

	for (size_t Idx = 0; Idx < m_SplitSprites.size(); ++Idx)
	{
		Target.draw(m_SplitSprites[Idx], States);
	}
}

void BigSprite::SetColor(const sf::Color& Color)
{
	m_Color = Color;

	for (size_t Idx = 0; Idx < m_SplitSprites.size(); ++Idx)
	{
		m_SplitSprites[Idx].setColor(Color);
	}
}

sf::Color BigSprite::GetColor()const
{
	return m_Color;
}

sf::FloatRect BigSprite::GetLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, m_Size.x, m_Size.y);
}

sf::FloatRect BigSprite::GetGlobalBounds() const
{
	return getTransform().transformRect(GetLocalBounds());
}

}
