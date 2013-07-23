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

	typedef std::pair<eTextureID::Val, float> TexIdPair;
	std::vector< TexIdPair > m_BodyTextures;
	int m_MaxHealth;
};

}