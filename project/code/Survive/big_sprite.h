#pragma once

#include <Survive/forward.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Survive
{

class BigSprite : public sf::Drawable, public sf::Transformable
{
public:

	BigSprite();

	explicit BigSprite(const BigTexture& texture);

	void SetTexture(const BigTexture& texture);

	void SetColor(const sf::Color& color);

	sf::Color GetColor()const;

	sf::FloatRect GetLocalBounds()const;
		
	sf::FloatRect GetGlobalBounds() const;

private:

	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States)const;

	std::vector<sf::Sprite>		m_SplitSprites;
	sf::Vector2f				m_Size;
	sf::Color					m_Color;
};

}
