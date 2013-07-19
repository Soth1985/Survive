#pragma once

#include <Survive/templates/template.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::ContentTemplate)

class ContentTemplate : public Template
{
public:

	ContentTemplate();

	virtual Type* GetType()const;

	std::array<std::string, eBigTextureID::BigTextureCount> m_BigTextures;
	std::array<std::string, eTextureID::TextureCount> m_Textures;
};

}