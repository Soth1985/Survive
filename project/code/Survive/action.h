#pragma once

#include <Survive/forward.h>
#include <Survive/type_info.h>

namespace Survive
{

class Action
{
public:

	typedef std::function<void(SceneNode*, float)> Function;

	Action();

	Function m_Action;
	Type* m_ReceiverType;
	int m_ReceiverId;
	bool m_DownCast;
};

template <class ObjectT, class FunctionT>
Action::Function DerivedAction(FunctionT Fn)
{
	return [=] (SceneNode* node, float Dt)
	{
		ObjectT* derivedNode = TypeCast<ObjectT>(node);
		
		assert(derivedNode != 0);

		Fn(derivedNode, Dt);
	};
}

}