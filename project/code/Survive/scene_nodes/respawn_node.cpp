#include <Survive/scene_nodes/respawn_node.h>
#include <Survive/scene_nodes/monster_entity_node.h>
#include <Survive/gui.h>
#include <Survive/settings.h>
#include <Survive/world.h>
#include <Survive/templates/respawn_template.h>
#include <Survive/templates/monster_template.h>
#include <Survive/math_utils.h>

namespace Survive
{

SURVIVE_REG_TYPE(RespawnNode, SURVIVE_TYPELIST_1(SceneNode))

RespawnNode::RespawnNode()
	:
m_pTemplate(0),
m_SpawnTimer(0.0f),
m_Size(sf::Vector2f(), sf::Vector2f(50.0f, 50.0f))
{

}

Type* RespawnNode::GetType()const
{
	return TypeImpl<RespawnNode>::Instance();
}

void RespawnNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{

}

void RespawnNode::OnUpdate(float Dt)
{
	if (m_pTemplate)
	{
		if (GetWorld()->GetNodeCount<MonsterEntityNode>() < GetWorld()->GetContext()->GetSettings()->GetMaxMonsterC())
		{
			QuadTreeNode::HitList Hits;
			GetWorld()->GetQuadTree()->GetObjects(m_Size, GetWorldTransform(), eCollisionGroup::Characters | eCollisionGroup::Static, Hits);

			if (!Hits.empty())
				return;

			m_SpawnTimer -= Dt;

			if (m_SpawnTimer <= 0.0f)
			{
				const MonsterTemplate* pMonsterToSpawn = MathUtils::GetRandomItem(m_pTemplate->m_Spawns).GetTemplate();
				MonsterEntityNode* pMonster = GetWorld()->CreateNode<MonsterEntityNode>(GetWorld()->GetLayerRoot(eWorldLayer::GroundLayer));
				pMonster->InitFromTemplate(pMonsterToSpawn);
				pMonster->SetLocalPosition(GetLocalPosition());
				m_SpawnTimer = m_pTemplate->m_SpawnFrequency;
			}
		}
	}
}

void RespawnNode::InitFromTemplate(const Template* pTmpl)
{
	const RespawnTemplate* pRespawnTmpl = TypeCast<RespawnTemplate>(pTmpl);

	if (pRespawnTmpl)
	{
		m_pTemplate = pRespawnTmpl;
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

}