#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/scene_nodes/static_sprite_node.h>
#include <Survive/templates/static_sprite_template.h>
#include <Survive/math_utils.h>
#include <Survive/debug_render.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(StaticSpriteEntityNode, SURVIVE_TYPELIST_1(StaticEntityNode))

Type* StaticSpriteEntityNode::GetType()const
{
	return TypeImpl<StaticSpriteEntityNode>::Instance();
}
	
void StaticSpriteEntityNode::InitFromTemplate(const Template* Tmpl)
{
	const StaticSpriteTemplate* pSpriteTmpl = TypeCast<StaticSpriteTemplate>(Tmpl);

	if (pSpriteTmpl)
	{
		eTextureID::Val TexId = MathUtils::GetRandomItem(pSpriteTmpl->m_Textures);
		const sf::Texture* pTex = GetWorld()->GetContext()->GetContentManager()->Textures().Get(TexId);

		if (pTex)
		{
			m_Sprite.setTexture(*pTex);
			sf::Vector2f Size(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height);
			m_Collision.SetSize(Size);
			m_Collision.SetCollisionGroup(eCollisionGroup::Static);
			GetWorld()->GetQuadTree()->AddObject(this);
		}
		else
			GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Texture not found.");
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid static sprite template type.");
	}
}

const CollisionShape* StaticSpriteEntityNode::GetCollisionShape()const
{
	return &m_Collision;
}

void StaticSpriteEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Sprite, States);
	GetWorld()->GetContext()->GetDebugRender()->AddAlignedBox(m_Collision, States.transform, 0.01f, sf::Color::Black);
}

void StaticSpriteEntityNode::OnUpdate(float Dt)
{
	
}

AlignedBoxShape StaticSpriteEntityNode::GetBounds()
{
	return m_Collision;
}

}