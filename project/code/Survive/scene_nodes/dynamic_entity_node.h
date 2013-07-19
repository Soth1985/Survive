#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/scene_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::DynamicEntityNode);

class DynamicEntityNode : public SceneNode
{
public:
private:

	sf::Vector2f m_Velocity;
};

}