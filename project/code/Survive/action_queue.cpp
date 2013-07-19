#include <Survive/action_queue.h>

namespace Survive
{

void ActionQueue::Push(const Action& Act)
{
	m_ActionQueue.push(Act);
}

Action ActionQueue::Pop()
{
	Action Act = m_ActionQueue.front();
	m_ActionQueue.pop();
	return Act;
}

bool ActionQueue::IsEmpty()const
{
	return m_ActionQueue.empty();
}

}