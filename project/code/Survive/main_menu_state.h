#pragma once

#include <Survive/forward.h>
#include <Survive/state.h>

#include <SFGUI/SFGUI.hpp>

namespace Survive
{

class MainMenuState: public State
{
public:

	MainMenuState(StateStack* pStack, Context* pContext);

	~MainMenuState();

	virtual void Draw();

	virtual bool Update(float Dt);

	virtual bool HandleEvent(const sf::Event& Event);

private:

	void OnExitClicked();

	void OnPlayClicked();

	sfg::Window::Ptr m_pWindow;
	sf::Sprite m_Background;
};

}