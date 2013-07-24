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

SURVIVE_REG_TYPE(RespawnEntityNode, SURVIVE_TYPELIST_1(SceneNode))

RespawnEntityNode::RespawnEntityNode()
	:
m_pTemplate(0),
m_SpawnTimer(0.0f),
m_Size(sf::Vector2f(), sf::Vector2f(50.0f, 50.0f))
{

}

Type* RespawnEntityNode::GetType()const
{
	return TypeImpl<RespawnEntityNode>::Instance();
}

void RespawnEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{

}

void RespawnEntityNode::OnUpdate(float Dt)
{
	if (GetInFrustrum())
		return;

	if (m_pTemplate)
	{
		if (GetWorld()->GetNodeCount<MonsterEntityNode>() < GetWorld()->GetContext()->GetSettings()->GetMaxMonsterC())
		{
			QuadTreeNode::HitList Hits;
			GetWorld()->GetQuadTree()->GetObjects(m_Size, GetWorldTransform(), eCollisionGroup::Characters | eCollisionGroup::Static, this, Hits);

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

AlignedBoxShape RespawnEntityNode::GetBounds()
{
	return m_Size;
}

const CollisionShape* RespawnEntityNode::GetCollisionShape()const
{
	return &m_Size;
}

void RespawnEntityNode::InitFromTemplate(const Template* pTmpl)
{
	SetUpdateFrequency(20, 50);
	const RespawnTemplate* pRespawnTmpl = TypeCast<RespawnTemplate>(pTmpl);

	if (pRespawnTmpl)
	{
		m_pTemplate = pRespawnTmpl;
		GetWorld()->GetQuadTree()->AddObject(this);
		m_Size.SetCollisionGroup(eCollisionGroup::Respawn);
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

}