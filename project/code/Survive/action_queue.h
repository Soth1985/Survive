#pragma once

#include <Survive/forward.h>
#include <Survive/action.h>

namespace Survive
{

class ActionQueue
{
public:

	void Push(const Action& Act);
	Action Pop();
	bool IsEmpty()const;

private:

	std::queue<Action> m_ActionQueue;
};

}