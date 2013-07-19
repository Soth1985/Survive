#pragma once

#include <Survive/forward.h>

namespace Survive
{

class RttiManager
{
public:

	void UnregisterType(Type* T);

	void RegisterType(Type* T);	

	Type* GetType(const char* Name);

	static RttiManager& Instance();

private:
	
	typedef std::unordered_map<const char*, Type*> TypeMap;	

	TypeMap m_RegisteredTypes;	
};

}