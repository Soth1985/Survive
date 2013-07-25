#include <Survive/scene_nodes/monster_entity_node.h>
#include <Survive/scene_nodes/pickup_entity_node.h>
#include <Survive/templates/pickup_template.h>
#include <Survive/scene_nodes/player_entity_node.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/world.h>
#include <Survive/templates/monster_template.h>
#include <Survive/math_utils.h>
#include <Survive/settings.h>

namespace Survive
{

SURVIVE_REG_TYPE(MonsterEntityNode, SURVIVE_TYPELIST_1(CharacterEntityNode))

MonsterEntityNode::MonsterEntityNode()
	:
m_pMonsterTmpl(0)
{

}

Type* MonsterEntityNode::GetType()const
{
	return TypeImpl<MonsterEntityNode>::Instance();
}

void MonsterEntityNode::InitFromTemplate(const Template* pTmpl)
{
	CharacterEntityNode::InitFromTemplate(pTmpl);

	if(GetCollisionShape())
		GetCollisionShapeModify()->SetCollisionGroup(eCollisionGroup::Monster);

	m_pMonsterTmpl = TypeCast<MonsterTemplate>(pTmpl);

	if (m_pMonsterTmpl)
	{
		
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid monster template type.");
	}
}

void MonsterEntityNode::OnUpdate(float Dt)
{
	CharacterEntityNode::OnUpdate(Dt);

	sf::Vector2f ChaseDir = GetWorld()->GetPlayer()->GetLocalPosition() - GetLocalPosition();
	ChaseDir = MathUtils::Normalize(ChaseDir);
	SetLocalRotation(MathUtils::RadToDeg(atan2f(ChaseDir.y, ChaseDir.x)) + 90.0f);
	sf::Vector2f MoveDisp = ChaseDir * m_pMonsterTmpl->m_MoveSpeed * Dt;
	DynamicMove(MoveDisp, false);

	if (GetInFrustrum())
		UseRangedWeapon(ChaseDir);
}

void MonsterEntityNode::OnEnterLeaveFrustrum(bool NewFrustrumState)
{
	if (NewFrustrumState)
	{
		SetUpdateFrequency(2, 4);
	}
	else
	{
		SetUpdateFrequency(20, 40);
	}
}

unsigned int MonsterEntityNode::GetBulletTraceMask()const
{
	return eCollisionGroup::Player | eCollisionGroup::Static;
}

void MonsterEntityNode::OnHit(int Damage)
{
	CharacterEntityNode::OnHit(Damage);

	if (GetHealth() <= 0)
	{
		GetWorld()->AddSceneNodeToRemove(this);
		Settings* pSettings = GetWorld()->GetContext()->GetSettings();
		pSettings->SetScore(pSettings->GetScore() + m_pMonsterTmpl->m_MaxHealth);

		float DropChance = MathUtils::RandomFloat();

		if (DropChance <= m_pMonsterTmpl->m_DropChance)
		{
			PickupEntityNode* pPickup = GetWorld()->CreateNode<PickupEntityNode>(GetWorld()->GetLayerRoot(eWorldLayer::PickupLayer));
			PickupTemplate* pPickUpTmpl = TemplateManager::Instance().GetTemplate<PickupTemplate>("PickupHealth");
			pPickup->InitFromTemplate(pPickUpTmpl);
			pPickup->SetLocalPosition(GetWorldPosition());
		}
	}
}

}