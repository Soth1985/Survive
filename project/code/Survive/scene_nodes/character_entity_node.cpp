#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/scene_nodes/character_entity_node.h>
#include <Survive/templates/character_template.h>
#include <Survive/math_utils.h>
#include <Survive/debug_render.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(CharacterEntityNode, SURVIVE_TYPELIST_1(DynamicEntityNode))

Type* CharacterEntityNode::GetType()const
{
	return TypeImpl<CharacterEntityNode>::Instance();
}
	
void CharacterEntityNode::InitFromTemplate(const Template* Tmpl)
{
	const CharacterTemplate* CharTmpl = TypeCast<CharacterTemplate>(Tmpl);

	if (CharTmpl)
	{
		eTextureID::Val BodyTexId = MathUtils::GetRandomItem(CharTmpl->m_BodyTextures);
		const sf::Texture* BodyTex = GetWorld()->GetContext()->GetContentManager()->Textures().Get(BodyTexId);

		if (BodyTex)
		{
			m_Body.setTexture(*BodyTex);
			sf::Vector2f HalfSize(m_Body.getLocalBounds().width / 2.0f, m_Body.getLocalBounds().height / 2.0f);
			m_Body.setOrigin(HalfSize);
			//HalfSize *= sqrtf(2.0f);
			m_Collision.SetCornerPosition(-HalfSize);
			m_Collision.SetSize(HalfSize * 2.0f);
			GetWorld()->GetQuadTree()->AddObject(this);
		}
		else
			GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Body texture not found.");
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

const CollisionShape* CharacterEntityNode::GetCollisionShape()const
{
	return &m_Collision;
}

void CharacterEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Body, States);	
	GetWorld()->GetContext()->GetDebugRender()->AddAlignedBox(m_Collision, GetWorldTransform(), 0.01f);
}

void CharacterEntityNode::OnUpdate(float Dt)
{
	
}

AlignedBoxShape CharacterEntityNode::GetBounds()
{
	return m_Collision;
}

}