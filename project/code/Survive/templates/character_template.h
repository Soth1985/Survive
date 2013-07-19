#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::CharacterTemplate)

class CharacterTemplate : public Template
{
public:

	CharacterTemplate();

	virtual Type* GetType()const;

	eTextureID::Val m_BodyTexture;
	int m_MaxHealth;
};

}