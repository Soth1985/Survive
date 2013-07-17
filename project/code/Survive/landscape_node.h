#pragma once

#include <Survive/forward.h>
#include <Survive/scene_node.h>
#include <Survive/big_sprite.h>

namespace Survive
{

class LandscapeNode: public SceneNode
{
public:

	LandscapeNode(const BigTexture* tex);

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	BigSprite m_Sprite;
};

}