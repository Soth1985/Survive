#include <Survive/scene_nodes/landscape_node.h>
#include <Survive/big_texture.h>
#include <Survive/world.h>

#include <SFML/Graphics/RenderTarget.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(LandscapeNode, SURVIVE_TYPELIST_1(SceneNode))

LandscapeNode::LandscapeNode()
{

}

void LandscapeNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Sprite, States);
}

void LandscapeNode::OnUpdate(float Dt)
{

}

Type* LandscapeNode::GetType()const
{
	return TypeImpl<LandscapeNode>::Instance();
}

void LandscapeNode::SetTexture(const BigTexture* tex)
{
	m_Sprite.SetTexture(*tex);
	sf::Vector2u TexSize = tex->GetSize();
	sf::Vector2f Size(TexSize.x, TexSize.y);
	m_Collision.SetSize(Size);
	m_Collision.SetCollisionGroup(eCollisionGroup::Landscape);
	GetWorld()->GetQuadTree()->AddObject(this);
}

AlignedBoxShape LandscapeNode::GetBounds()
{
	return m_Collision;
}

const CollisionShape* LandscapeNode::GetCollisionShape()const
{
	return &m_Collision;
}

}