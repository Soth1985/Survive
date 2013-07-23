#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/character_entity_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::MonsterEntityNode);

class MonsterEntityNode : public CharacterEntityNode
{
public:

	virtual void InitFromTemplate(const Template* pTmpl);

	virtual Type* GetType()const;

protected:

	virtual void OnUpdate(float Dt);
};

}