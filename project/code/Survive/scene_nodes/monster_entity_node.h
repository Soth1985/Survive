#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/character_entity_node.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::MonsterEntityNode);

class MonsterEntityNode : public CharacterEntityNode
{
public:

	MonsterEntityNode();

	virtual void InitFromTemplate(const Template* pTmpl);

	virtual Type* GetType()const;

	virtual unsigned int GetBulletTraceMask()const;

	virtual void OnHit(int Damage);

protected:

	virtual void OnEnterLeaveFrustrum(bool NewFrustrumState);

	virtual void OnUpdate(float Dt);

private:

	const MonsterTemplate* m_pMonsterTmpl;
};

}