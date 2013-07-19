#include <Survive/state_stack.h>
#include <Survive/state.h>

namespace Survive
{

StateStack::StateStack(Context* pContext)
	: 
m_pContext(pContext)
{
}

StateStack::~StateStack()
{

}

void StateStack::Update(float Dt)
{
	for (auto It = m_Stack.rbegin(); It != m_Stack.rend(); ++It)
	{
		if (!(*It)->Update(Dt))
			break;
	}

	ApplyPendingChanges();
}

void StateStack::Draw()
{
	for(auto It = m_Stack.begin(); It != m_Stack.end(); ++It)
	{
		(*It)->Draw();
	}
}

void StateStack::HandleEvent(const sf::Event& Event)
{
	for (auto It = m_Stack.rbegin(); It != m_Stack.rend(); ++It)
	{
		if (!(*It)->HandleEvent(Event))
			break;
	}

	ApplyPendingChanges();
}

void StateStack::PushState(eStateID::Val StateID)
{
	m_PendingList.push_back(PendingChange(Push, StateID));
}

void StateStack::PopState()
{
	m_PendingList.push_back(PendingChange(Pop));
}

void StateStack::ClearStates()
{
	m_PendingList.push_back(PendingChange(Clear));
}

bool StateStack::IsEmpty()const
{
	return m_Stack.empty();
}

StatePtr StateStack::CreateState(eStateID::Val StateID)
{
	auto Found = m_Factories.find(StateID);
	assert(Found != m_Factories.end());

	return Found->second();
}

void StateStack::ApplyPendingChanges()
{
	for(auto It = m_PendingList.begin(); It != m_PendingList.end(); ++It)
	{
		switch (It->m_Action)
		{
		case Push:
			m_Stack.push_back(CreateState(It->m_StateID));
			break;

		case Pop:
			m_Stack.pop_back();
			break;

		case Clear:
			m_Stack.clear();
			break;
		}
	}

	m_PendingList.clear();
}

StateStack::PendingChange::PendingChange(StackAction Act, eStateID::Val StateID)
	: 
m_Action(Act),
m_StateID(StateID)
{
}

}
