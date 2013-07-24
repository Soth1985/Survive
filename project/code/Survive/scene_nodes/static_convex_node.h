#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/static_entity_node.h>
#include <Survive/collision/convex_polygon_shape.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::StaticConvexEntityNode);

class StaticConvexEntityNode : public StaticEntityNode
{
public:

	virtual Type* GetType()const;

	virtual void InitFromTemplate(const Template* pTmpl);

	virtual AlignedBoxShape GetBounds();

	virtual const CollisionShape* GetCollisionShape()const;

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	sf::ConvexShape m_Shape;
	ConvexPolygonShape m_Collision;
};

}