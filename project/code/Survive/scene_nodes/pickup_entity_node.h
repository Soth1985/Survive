#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/dynamic_entity_node.h>
#include <SFML/Graphics/Sprite.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PickupEntityNode);

class PickupEntityNode : public DynamicEntityNode
{
public:

	PickupEntityNode();

	virtual Type* GetType()const;

	virtual AlignedBoxShape GetBounds();

	virtual const CollisionShape* GetCollisionShape()const;

	virtual void InitFromTemplate(const Template* pTmpl);

	int GetHealthToGive()const;

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	sf::Sprite m_Sprite;
	AlignedBoxShape m_Collision;
	const PickupTemplate* m_pPickupTmpl;
};

}