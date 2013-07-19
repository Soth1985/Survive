#pragma once

#include <Survive/forward.h>

#include <SFGUI/SFGUI.hpp>

namespace Survive
{

class Gui
{
public:

	void HandleEvent(const sf::Event& Event);
	void Update(float Dt);
	void Draw(sf::RenderWindow* pWindow);
	void AddWindow(sfg::Window::Ptr pWindow);
	void RemoveWindow(sfg::Window::Ptr pWindow);
	
	sfg::Desktop& GetDesktop()
	{
		return m_Desktop;
	}

	static void PlaceToCenter(sfg::Window::Ptr pGuiWindow, sf::RenderWindow* pRenderWindow);

private:
	sfg::SFGUI m_Sfgui;
	sfg::Desktop m_Desktop;
};

}