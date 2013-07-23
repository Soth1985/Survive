#include <Survive/scene_nodes/static_entity_node.h>

namespace Survive
{

SURVIVE_REG_TYPE(StaticEntityNode, SURVIVE_TYPELIST_1(SceneNode))

Type* StaticEntityNode::GetType()const
{
	return TypeImpl<StaticEntityNode>::Instance();
}

}