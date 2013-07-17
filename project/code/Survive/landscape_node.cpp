#include <Survive/landscape_node.h>

#include <SFML/Graphics/RenderTarget.hpp>

namespace Survive
{

LandscapeNode::LandscapeNode(const BigTexture* tex)
	:
m_Sprite(*tex)
{

}

void LandscapeNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Sprite, States);
}

void LandscapeNode::OnUpdate(float Dt)
{

}

}