#include <Survive/state.h>
#include <Survive/state_stack.h>

namespace Survive
{

State::State(StateStack* pStack, Context* pContext)
	: 
m_pStack(pStack),
m_pContext(pContext)
{
}

State::~State()
{
}

void State::RequestStackPush(eStateID::Val StateID)
{
	m_pStack->PushState(StateID);
}

void State::RequestStackPop()
{
	m_pStack->PopState();
}

void State::RequestStateClear()
{
	m_pStack->ClearStates();
}

Context* State::GetContext()const
{
	return m_pContext;
}

}
