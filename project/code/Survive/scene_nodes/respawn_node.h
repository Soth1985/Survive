#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/scene_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::RespawnEntityNode);

class RespawnEntityNode : public SceneNode
{
public:

	RespawnEntityNode();

	virtual Type* GetType()const;

	virtual void InitFromTemplate(const Template* pTmpl);

	virtual AlignedBoxShape GetBounds();

	virtual const CollisionShape* GetCollisionShape()const;

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	float m_SpawnTimer;
	AlignedBoxShape m_Size;
	const RespawnTemplate* m_pTemplate;
};

}