#include <Survive/scene_nodes/monster_entity_node.h>
#include <Survive/scene_nodes/player_entity_node.h>
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

void MonsterEntityNode::InitFromTemplate(const Template* pTmpl)
{
	CharacterEntityNode::InitFromTemplate(pTmpl);

	if(GetCollisionShape())
		GetCollisionShapeModify()->SetCollisionGroup(eCollisionGroup::Monster);

	const MonsterTemplate* pMonsterTmpl = TypeCast<MonsterTemplate>(pTmpl);

	if (pMonsterTmpl)
	{
		
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid monster template type.");
	}
}

void MonsterEntityNode::OnUpdate(float Dt)
{
	sf::Vector2f ChaseDir = GetWorld()->GetPlayer()->GetLocalPosition() - GetLocalPosition();
	ChaseDir = MathUtils::Normalize(ChaseDir);
	ChaseDir *= 100.0f * Dt;
	Move(ChaseDir);

	CharacterEntityNode::OnUpdate(Dt);
}

}