#include <Survive/scene_nodes/monster_entity_node.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/world.h>
#include <Survive/templates/monster_template.h>
#include <Survive/math_utils.h>

namespace Survive
{

SURVIVE_REG_TYPE(MonsterEntityNode, SURVIVE_TYPELIST_1(CharacterEntityNode))


Type* MonsterEntityNode::GetType()const
{
	return TypeImpl<MonsterEntityNode>::Instance();
}

void MonsterEntityNode::InitFromTemplate(Template* pTmpl)
{
	CharacterEntityNode::InitFromTemplate(pTmpl);

	if(GetCollisionShape())
		GetCollisionShapeModify()->SetCollisionGroup(eCollisionGroup::Monster);

	MonsterTemplate* pMonsterTmpl = TypeCast<MonsterTemplate>(pTmpl);

	if (pMonsterTmpl)
	{
		
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

void MonsterEntityNode::OnUpdate(float Dt)
{
	CharacterEntityNode::OnUpdate(Dt);
}

}