#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::WeaponTemplate)

class WeaponTemplate : public Template
{
public:

	WeaponTemplate();

	virtual Type* GetType()const;

	eTextureID::Val m_Texture;
};

}