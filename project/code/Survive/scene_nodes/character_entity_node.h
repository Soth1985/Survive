#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/dynamic_entity_node.h>

#include <SFML/Graphics/Sprite.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CharacterEntityNode);

class CharacterEntityNode : public DynamicEntityNode
{
public:

	void InitFromTemplate(Template* Tmpl);

	virtual sf::FloatRect GetBounds();

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	sf::Sprite m_Body;	
};

}