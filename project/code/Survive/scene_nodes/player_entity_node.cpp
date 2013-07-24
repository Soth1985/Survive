#include <Survive/scene_nodes/player_entity_node.h>
#include <Survive/templates/player_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(PlayerEntityNode, SURVIVE_TYPELIST_1(CharacterEntityNode))

Type* PlayerEntityNode::GetType()const
{
	return TypeImpl<PlayerEntityNode>::Instance();
}

void PlayerEntityNode::InitFromTemplate(const Template* Tmpl)
{
	CharacterEntityNode::InitFromTemplate(Tmpl);

	if(GetCollisionShape())
		GetCollisionShapeModify()->SetCollisionGroup(eCollisionGroup::Player);

	m_pPlayerTmpl = TypeCast<PlayerTemplate>(Tmpl);
}

unsigned int PlayerEntityNode::GetBulletTraceMask()const
{
	return eCollisionGroup::Monster | eCollisionGroup::Static;
}

void PlayerEntityNode::OnHit(int Damage)
{
	CharacterEntityNode::OnHit(Damage);
}

}