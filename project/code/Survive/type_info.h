#pragma once


#include <type_traits>
#include <Survive/forward.h>
#include <Survive/type_lists.h>
#include <Survive/rtti_manager.h>

namespace Survive
{

template <class T>
struct ClassName;

#define SURVIVE_DECL_TYPE(t) \
	template<> struct Survive::ClassName<t>\
	{\
	static const char* GetName()\
	{\
		return #t;\
	}\
	};

class Type
{
public:

	virtual const char* GetName()const=0;	
	virtual bool		IsBaseOf(Type* C)const=0;
	virtual bool		IsChildOf(Type* C)const=0;
	virtual bool		IsAbstract()const=0;
	virtual size_t		GetNumBases()const=0;
	virtual Type*		GetBaseAt(size_t Idx)=0;
	virtual size_t		GetNumChildren()const=0;
	virtual Type*		GetChildAt(size_t Idx)=0;
	virtual bool		IsFundamental()const=0;
	virtual size_t		GetSize()const=0;

	template<class T>
	T* CreateObject(int Param = 0)
	{
		Type* Tp = TypeOf<T>();
		if(this == Tp || this->IsChildOf(Tp) )
		{
			return (T*)CreateObject(Param);
		}
		else
			return 0;
	}

	virtual void* CreateObject(int Param = 0) = 0;

	virtual ~Type()
	{
		//
	}	

private:
	friend class RttiManager;

	template <class T>
	friend class TypeImpl;
	
	virtual void RemoveType(Type* T)=0;
	virtual void AddChild(Type* T)=0;
	virtual void AddBase(Type* T)=0;
};

namespace Private
{

template<class T, bool Abstract>
struct CreateClassInstance;

template<class T>
struct CreateClassInstance<T, true>
{
	static void* Create(int Param)
	{
		return 0;
	}
};

template<class T>
struct CreateClassInstance<T, false>
{
	static void* Create(int Param)
	{
		return new T();
	}
};

}//Private

template <class T>
class TypeImpl : public Type
{
public:	

	virtual const char* GetName()const
	{
		return ClassName<T>::GetName();
	}	

	virtual bool IsBaseOf(Type* C)const
	{
		ClassList::const_iterator It = m_Children.find(C);
		return It != m_Children.end();
	}

	virtual bool IsChildOf(Type* C)const
	{
		ClassList::const_iterator It = m_Bases.find(C);
		return It != m_Bases.end();
	}

	virtual bool IsAbstract()const
	{
		return std::tr1::is_abstract<T>::value;
	}

	virtual size_t GetNumBases()const
	{
		return m_Bases.size();
	}

	virtual Type* GetBaseAt(size_t Idx)
	{
		if( Idx < m_Bases.size() )
		{
			size_t Res = 0;
			ClassList::iterator It = m_Bases.begin();

			for(; Res < Idx; ++It,++Res){};
			return *It;
		}

		return 0;
	}

	virtual size_t GetNumChildren()const
	{
		return m_Children.size();
	}

	virtual Type* GetChildAt(size_t Idx)
	{
		if( Idx < m_Children.size() )
		{
			size_t Res = 0;
			ClassList::iterator It = m_Children.begin();

			for(; Res < Idx; ++It,++Res){};
			return *It;
		}

		return 0;
	}

	virtual bool IsFundamental()const
	{
		return std::tr1::is_fundamental<T>::value;
	}

	virtual size_t GetSize()const
	{
		return sizeof(T);
	}	

	virtual void RemoveType(Type* T)
	{
		for(ClassList::iterator It = m_Bases.begin(); It != m_Bases.end(); ++It)
		{
			if( T == *It )
			{
				m_Bases.erase(It);
				break;
			}
		}

		for(ClassList::iterator It = m_Children.begin(); It != m_Children.end(); ++It)
		{
			if( T == *It )
			{
				m_Children.erase(It);
				break;
			}
		}
	}

	~TypeImpl()
	{
	}

	static Type* Instance()
	{
		static TypeImpl instance;
		return &instance;
	}	

	template<class Parents>
	static void SetParents()
	{
		ProcessParents<Parents>::Process();
	}

	virtual void* CreateObject(int Param)
	{
		return Private::CreateClassInstance<T, std::tr1::is_abstract<T>::value>::Create(Param);
	}

private:

	TypeImpl()
	{		
		RttiManager::Instance().RegisterType(this);
	}

	virtual void AddChild(Type* T)
	{
		m_Children.insert(T);

		for(ClassList::iterator It = m_Bases.begin(); It != m_Bases.end(); ++It)
			(*It)->AddChild(T);
	}

	virtual void AddBase(Type* T)
	{
		m_Bases.insert(T);

		for(size_t Idx = 0; Idx < T->GetNumBases(); ++Idx)
		{
			m_Bases.insert( T->GetBaseAt(Idx) );
		}

		for(ClassList::iterator It = m_Children.begin(); It != m_Children.end(); ++It)
			(*It)->AddBase(T);
	}	

	template<class Parent>
	struct ProcessParents
	{
		static void Process()
		{
			static_assert( (std::tr1::is_base_of<Parent, T>::value), "These classes are not related" );			
			Type* parent = TypeImpl<Parent>::Instance();
			Type* thisType = TypeImpl<T>::Instance();

			parent->AddChild(thisType);
			thisType->AddBase(parent);
		}
	};

	template<>
	struct ProcessParents<NullType>
	{
		static void Process()
		{
			
		}
	};

	template<class Head, class Tail>
	struct ProcessParents< Typelist<Head, Tail> >
	{
		static void Process()
		{
			ProcessParents<Head>::Process();
			ProcessParents<Tail>::Process();
		}
	};
	

	template<class Ty, class Parents>
	friend struct RegisterType;

	typedef std::unordered_set<Type*> ClassList;

	ClassList	m_Bases;
	ClassList	m_Children;
};

template<class Ty, class Parents>
struct RegisterType
{
	RegisterType()
	{
		TypeImpl<Ty>::Instance();
		TypeImpl<Ty>::SetParents<Parents>();		
	}	
};

template<class Ty>
struct RegisterType< Ty, SURVIVE_TYPELIST_0() >
{
	RegisterType()
	{		
		TypeImpl<Ty>::Instance();
	}	
};

template<class T>
bool IsOfType(Type* Tp)
{
	return Tp == TypeImpl<T>::Instance();
}

template<class T>
Type* TypeOf()
{
	return TypeImpl<T>::Instance();
}

static bool IsConvertible(Type* From, Type* To)
{
	if( From == To || From->IsChildOf(To) )
	{
		return true;
	}
	else
		return false;
}

template <class TgtT, class SrcT>
TgtT* TypeCast(SrcT* Src)
{
	TgtT* Result=0;

	if(Src)
	{
		Type* SrcType = Src->GetType();
		Type* TgtType = TypeImpl<TgtT>::Instance();

		if( IsConvertible(SrcType, TgtType) )
		{
			Result = static_cast<TgtT*>(Src);
		}
	}

	return Result;
}

template <class TgtT, class SrcT>
const TgtT* TypeCast(const SrcT* Src)
{
	const TgtT* Result=0;

	if(Src)
	{
		Type* SrcType = Src->GetType();
		Type* TgtType = TypeImpl<TgtT>::Instance();

		if( IsConvertible(SrcType, TgtType) )
		{
			Result = static_cast<const TgtT*>(Src);
		}
	}

	return Result;
}

#define SURVIVE_REG_ROOT_TYPE(t) static Survive::RegisterType<t, SURVIVE_TYPELIST_0()> thor_rtti_##t;
#define SURVIVE_REG_TYPE(t, parents) static Survive::RegisterType<t, parents> thor_rtti_##t;

}//Thor