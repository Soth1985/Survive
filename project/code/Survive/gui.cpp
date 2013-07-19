#include <Survive/gui.h>

namespace Survive
{

void Gui::HandleEvent(const sf::Event& Event)
{
	m_Desktop.HandleEvent(Event);
}

void Gui::Update(float Dt)
{
	m_Desktop.Update(Dt);
}

void Gui::Draw(sf::RenderWindow* pWindow)
{
	m_Sfgui.Display(*pWindow);
}

void Gui::AddWindow(sfg::Window::Ptr pWindow)
{
	m_Desktop.Add(pWindow);
}

void Gui::RemoveWindow(sfg::Window::Ptr pWindow)
{
	m_Desktop.Remove(pWindow);
}

void Gui::PlaceToCenter(sfg::Window::Ptr pGuiWindow, sf::RenderWindow* pRenderWindow)
{
	pGuiWindow->SetPosition(
		sf::Vector2f(
		static_cast<float>( pRenderWindow->getSize().x / 2 ) - pGuiWindow->GetAllocation().width / 2.f,
		static_cast<float>( pRenderWindow->getSize().y / 2 ) - pGuiWindow->GetAllocation().height / 2.f
		)
		);
}

}