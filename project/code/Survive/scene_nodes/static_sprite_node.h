#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/static_entity_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::StaticSpriteNode);

class StaticSpriteNode : public StaticEntityNode
{
public:

	StaticSpriteNode();

	virtual Type* GetType()const;

	virtual void InitFromTemplate(const Template* pTmpl);

	virtual AlignedBoxShape GetBounds();

	virtual const CollisionShape* GetCollisionShape()const;

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	sf::Sprite m_Sprite;
	AlignedBoxShape m_Collision;
};

}