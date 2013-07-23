#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/scene_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::RespawnNode);

class RespawnNode : public SceneNode
{
public:
	virtual Type* GetType()const;
private:
};

}