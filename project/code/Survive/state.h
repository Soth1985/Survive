#pragma once

#include <Survive/forward.h>

namespace Survive
{

class State
{
public:

	State(StateStack* pStack, Context* pContext);
	
	virtual ~State();

	virtual void Draw() = 0;
	
	virtual bool Update(float Dt) = 0;
	
	virtual bool HandleEvent(const sf::Event& Event) = 0;

protected:

	void RequestStackPush(eStateID::Val StateID);
	void RequestStackPop();
	void RequestStateClear();

	Context* GetContext()const;

private:
	StateStack* m_pStack;
	Context* m_pContext;
};

}