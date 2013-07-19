#pragma once

#include <Survive/forward.h>
#include <Survive/type_info.h>
#include <Survive/templates/template.h>

namespace Survive
{

class TemplateManager
{
public:

	TemplateManager();

	~TemplateManager();

	template<class TemplateT>
	bool AddTemplate(const std::string& Name, Template* Tmpl)
	{
		TemplateMap* Map = GetTemplateMap(TypeImpl<TemplateT>::Instance());

		if (Map)
		{
			(*Map)[Name].reset(Tmpl);
			return true;
		}
		else
			return false;
	}

	template <class TemplateT>
	TemplateT* GetTemplate(const std::string& Name)
	{
		TemplateMap* Map = GetTemplateMap(TypeImpl<TemplateT>::Instance());

		if (Map)
		{
			TemplateMap::iterator It = Map->find(Name);

			if (It != Map->end())
				return static_cast<TemplateT*>(It->second.get());
			else
				return 0;
		}
		else
			return 0;
	}

	template <class TemplateT>
	bool RemoveTemplate(const std::string& Name)
	{
		TemplateMap* Map = GetTemplateMap(TypeImpl<TemplateT>::Instance());

		if (Map)
		{
			return Map->erase(Name) != 0;
		}
		else
			return false;
	}

	static TemplateManager& Instance();

private:

	typedef std::unordered_map<std::string, TemplatePtr> TemplateMap;
	typedef std::unordered_map<Type*, TemplateMap> TemplateTypeMap;

	TemplateMap* GetTemplateMap(Type* TmplType);
	Type* CheckType(Type* TmplType);
	void CreateDefaultTemplates();

	TemplateTypeMap m_Templates;
};

}