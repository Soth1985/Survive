#pragma once

#include <Survive/templates/static_object_template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::StaticSpriteTemplate)

class StaticSpriteTemplate : public StaticObjectTemplate
{
public:

	virtual Type* GetType()const;

	typedef std::pair<eTextureID::Val, float> TexIdPair;
	std::vector< TexIdPair > m_Textures;
};

}