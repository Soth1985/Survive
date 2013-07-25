#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::PickupTemplate)

class PickupTemplate : public Template
{
public:

	PickupTemplate();

	virtual Type* GetType()const;

	eTextureID::Val m_TexId;
	int m_HealthToGive;
};

}