#include <Survive/scene_nodes/pickup_entity_node.h>
#include <Survive/templates/pickup_template.h>
#include <Survive/content_manager.h>
#include <Survive/world.h>
#include <Survive/math_utils.h>
#include <Survive/gui.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(PickupEntityNode, SURVIVE_TYPELIST_1(DynamicEntityNode))

PickupEntityNode::PickupEntityNode()
	:
m_pPickupTmpl(0)
{

}

void PickupEntityNode::InitFromTemplate(const Template* pTmpl)
{
	m_pPickupTmpl = TypeCast<PickupTemplate>(pTmpl);

	if (m_pPickupTmpl)
	{
		const sf::Texture* pTex = GetWorld()->GetContext()->GetContentManager()->Textures().Get(m_pPickupTmpl->m_TexId);
		m_Sprite.setTexture(*pTex);
		m_Collision.SetCollisionGroup(eCollisionGroup::Pickup);
		m_Collision.SetSize(sf::Vector2f(pTex->getSize().x, pTex->getSize().y));
		GetWorld()->GetQuadTree()->AddObject(this);
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

Type* PickupEntityNode::GetType()const
{
	return TypeImpl<PickupEntityNode>::Instance();
}

AlignedBoxShape PickupEntityNode::GetBounds()
{
	return m_Collision;
}

const CollisionShape* PickupEntityNode::GetCollisionShape()const
{
	return &m_Collision;
}

int PickupEntityNode::GetHealthToGive()const
{
	return m_pPickupTmpl->m_HealthToGive;
}

void PickupEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Sprite, States);
}

void PickupEntityNode::OnUpdate(float Dt)
{

}

}