#pragma once

#include <Survive/forward.h>
#include <Survive/templates/template_manager.h>

namespace Survive
{

template <class T>
class TemplateRef
{
public:

	TemplateRef()
	{

	}

	TemplateRef(const std::string& TemplateName)
		:
	m_TemplateName(TemplateName)
	{

	}

	T* GetTemplate()
	{
		return TemplateManager::Instance().GetTemplate<T>(m_TemplateName);
	}

	void SetTemplateName(const std::string& TemplateName)
	{
		m_TemplateName = TemplateName;
	}

private:

	std::string m_TemplateName;
};

}