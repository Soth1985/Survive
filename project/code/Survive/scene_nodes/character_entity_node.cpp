#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/scene_nodes/character_entity_node.h>
#include <Survive/templates/character_template.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(CharacterEntityNode, SURVIVE_TYPELIST_1(DynamicEntityNode))

void CharacterEntityNode::InitFromTemplate(Template* Tmpl)
{
	CharacterTemplate* CharTmpl = TypeCast<CharacterTemplate>(Tmpl);

	if (CharTmpl)
	{
		const sf::Texture* BodyTex = GetWorld()->GetContext()->GetContentManager()->Textures().Get(CharTmpl->m_BodyTexture);

		if (BodyTex)
		{
			m_Body.setTexture(*BodyTex);
			sf::Vector2f HalfSize(m_Body.getLocalBounds().width / 2.0f, m_Body.getLocalBounds().height / 2.0f);
			m_Body.setOrigin(HalfSize);
		}
		else
			GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Body texture not found.");
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

void CharacterEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Body, States);	
}

void CharacterEntityNode::OnUpdate(float Dt)
{

}

sf::FloatRect CharacterEntityNode::GetBounds()
{
	return m_Body.getGlobalBounds();
}

}