#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/scene_node.h>
#include <Survive/big_sprite.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::LandscapeNode);

class LandscapeNode: public SceneNode
{
public:

	LandscapeNode();

	virtual Type* GetType()const;

	void SetTexture(const BigTexture* tex);

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	BigSprite m_Sprite;
};

}