#pragma once

#include <Survive/forward.h>

namespace Survive
{

template<class ResT, class IdT>
class ContentHolder
{
public:

	const ResT* Get(const IdT& id)const
	{
		ResourcesMap::const_iterator It = m_Resources.find(id);

		if (It != m_Resources.end())
			return It->second.get();
		else
			return 0;
	}

	void Set(const IdT& id, ResT* resource)
	{
		m_Resources[id].reset(resource);
	}

private:

	typedef std::unique_ptr<ResT> ResourcePtr;
	typedef std::unordered_map<IdT, ResourcePtr> ResourcesMap;
	ResourcesMap m_Resources;
};

}