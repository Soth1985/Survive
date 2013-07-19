#pragma once

#include <Survive/forward.h>

#include <SFGUI/SFGUI.hpp>

namespace Survive
{

class Gui
{
public:

	Gui(Settings* pSettings);

	void HandleEvent(const sf::Event& Event);
	void Update(float Dt);
	void Draw(sf::RenderWindow* pWindow);
	void AddWindow(sfg::Window::Ptr pWindow);
	void RemoveWindow(sfg::Window::Ptr pWindow);
	void MessageBox(const std::string& Caption, const std::string& Message);
	void Reset();
	
	sfg::Desktop& GetDesktop()
	{
		return m_Desktop;
	}

	static void PlaceToCenter(sfg::Window::Ptr pGuiWindow, int ParentWidth, int ParentHeight);

private:

	void RemoveMessageBox();

	sfg::SFGUI m_Sfgui;
	sfg::Desktop m_Desktop;
	Settings* m_pSettings;
};

}