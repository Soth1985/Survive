#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/character_entity_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PlayerEntityNode);

class PlayerEntityNode : public CharacterEntityNode
{
public:

	virtual void InitFromTemplate(const Template* Tmpl);
	virtual Type* GetType()const;

private:
};

}