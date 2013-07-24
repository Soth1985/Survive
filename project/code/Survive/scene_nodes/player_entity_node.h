#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/character_entity_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PlayerEntityNode);

class PlayerEntityNode : public CharacterEntityNode
{
public:

	virtual void InitFromTemplate(const Template* Tmpl);

	virtual unsigned int GetBulletTraceMask()const;

	virtual Type* GetType()const;

	virtual void OnHit(int Damage);

private:

	const PlayerTemplate* m_pPlayerTmpl;
};

}