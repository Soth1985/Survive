#pragma once

#include <Survive/forward.h>
#include <Survive/state.h>

#include <SFGUI/SFGUI.hpp>

namespace Survive
{

class GameOverState: public State
{
public:

	GameOverState(StateStack* pStack, Context* pContext);

	~GameOverState();

	virtual void Draw();

	virtual bool Update(float Dt);

	virtual bool HandleEvent(const sf::Event& Event);

private:

	sf::Sprite m_Background;
	sf::Text m_Text;
};

}