#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/scene_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::RespawnNode);

class RespawnNode : public SceneNode
{
public:

	RespawnNode();

	virtual Type* GetType()const;

	virtual void InitFromTemplate(const Template* pTmpl);

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	float m_SpawnTimer;
	AlignedBoxShape m_Size;
	const RespawnTemplate* m_pTemplate;
};

}