#pragma once

#include <Survive/templates/template.h>
#include <Survive/templates/template_ref.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::RespawnTemplate)

class RespawnTemplate : public Template
{
public:

	RespawnTemplate();

	virtual Type* GetType()const;

	typedef TemplateRef<MonsterTemplate> Spawn;
	typedef std::pair< Spawn, float > SpawnPair;

	std::vector<SpawnPair> m_Spawns;
	float m_SpawnFrequency;
	int m_MaxSpawnCount;
};

}