#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/dynamic_entity_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PickupEntityNode);

class PickupEntityNode : public DynamicEntityNode
{
public:
	virtual Type* GetType()const;
private:
};

}