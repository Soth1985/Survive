#include <Survive/rtti_manager.h>
#include <Survive/type_info.h>

namespace Survive
{

void RttiManager::UnregisterType(Type* T)
{
	m_RegisteredTypes.erase(T->GetName());
}

void RttiManager::RegisterType(Type* T)
{	
	if( m_RegisteredTypes.insert( TypeMap::value_type(T->GetName(), T)).second == false)
	{
		assert(0 && "Attempt to register multiple types under the name ");
	}
}

Type* RttiManager::GetType(const char* Name)
{
	TypeMap::iterator t = m_RegisteredTypes.find(Name);

	if( t != m_RegisteredTypes.end() )
		return t->second;
	
	return 0;
}

RttiManager& RttiManager::Instance()
{
	static RttiManager RttiMngr;
	return RttiMngr;
}

}
