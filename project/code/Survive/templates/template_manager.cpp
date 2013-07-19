#include <Survive/templates/template_manager.h>

#include <Survive/templates/content_template.h>

namespace Survive
{

TemplateManager::TemplateManager()
{
	CreateDefaultTemplates();
}

TemplateManager::~TemplateManager()
{

}

TemplateManager& TemplateManager::Instance()
{
	static TemplateManager Inst;
	return Inst;
}

TemplateManager::TemplateMap* TemplateManager::GetTemplateMap(Type* TmplType)
{
	TmplType = CheckType(TmplType);

	if (TmplType)
	{
		return &m_Templates[TmplType];
	}
	else
		return 0;
}

Type* TemplateManager::CheckType(Type* TmplType)
{
	Type* BaseType = TypeImpl<Template>::Instance();

	if (IsConvertible(TmplType, BaseType))
	{
		return TmplType;
	}
	else
	{
		assert(0 && "Not a template");
		return 0;
	}
}

void TemplateManager::CreateDefaultTemplates()
{
	ContentTemplate* ContentTmpl = new ContentTemplate();

	AddTemplate<ContentTemplate>("Content", ContentTmpl);
}

}