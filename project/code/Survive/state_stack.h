#pragma once

#include <Survive/forward.h>

namespace Survive
{

class StateStack
{
public:

	enum StackAction
	{
		Push,
		Pop,
		Clear,
	};

	StateStack(Context* pContext);

	~StateStack();

	template <typename T>
	void RegisterState(eStateID::Val StateID)
	{
		m_Factories[StateID] = [this] ()
		{
			return StatePtr(new T(this, m_pContext));
		};
	}

	void Update(float Dt);

	void Draw();
	
	void HandleEvent(const sf::Event& Event);

	void PushState(eStateID::Val StateID);
	
	void PopState();
	
	void ClearStates();

	bool IsEmpty()const;

private:

	struct PendingChange
	{
		PendingChange(StackAction Act, eStateID::Val StateID = eStateID::None);

		StackAction m_Action;
		eStateID::Val m_StateID;
	};

	StatePtr CreateState(eStateID::Val StateID);
	void ApplyPendingChanges();

	std::vector<StatePtr> m_Stack;
	std::vector<PendingChange> m_PendingList;
	Context* m_pContext;
	std::map<eStateID::Val, std::function<StatePtr()>> m_Factories;
};

}