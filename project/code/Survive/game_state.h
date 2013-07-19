#pragma once

#include <Survive/forward.h>
#include <Survive/state.h>

#include <SFGUI/SFGUI.hpp>

namespace Survive
{

class GameState: public State
{
public:

	GameState(StateStack* pStack, Context* pContext);

	~GameState();

	virtual void Draw();

	virtual bool Update(float Dt);

	virtual bool HandleEvent(const sf::Event& Event);

private:

	void OnMenuResumeClicked();

	void OnMenuReturnClicked();

	sfg::Window::Ptr m_pMenuWindow;
	bool m_Paused;
};

}