#include <Survive/scene_nodes/player_entity_node.h>

namespace Survive
{

SURVIVE_REG_TYPE(PlayerEntityNode, SURVIVE_TYPELIST_1(CharacterEntityNode))

Type* PlayerEntityNode::GetType()const
{
	return TypeImpl<PlayerEntityNode>::Instance();
}

void PlayerEntityNode::InitFromTemplate(Template* Tmpl)
{
	CharacterEntityNode::InitFromTemplate(Tmpl);

	if(GetCollisionShape())
		GetCollisionShapeModify()->SetCollisionGroup(eCollisionGroup::Player);
}

}