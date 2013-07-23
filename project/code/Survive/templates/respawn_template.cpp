#include <Survive/templates/respawn_template.h>

namespace Survive
{

SURVIVE_REG_TYPE(RespawnTemplate, SURVIVE_TYPELIST_1(Template))

RespawnTemplate::RespawnTemplate()
	:
m_SpawnFrequency(1.0f),
m_MaxSpawnCount(-1)
{

}

Type* RespawnTemplate::GetType()const
{
	return TypeImpl<RespawnTemplate>::Instance();
}

}