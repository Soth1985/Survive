#include <Survive/gui.h>
#include <Survive/settings.h>

#include <windows.h>

namespace Survive
{

Gui::Gui(Settings* pSettings)
	:
m_pSettings(pSettings)
{

}

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

void Gui::PlaceToCenter(sfg::Window::Ptr pGuiWindow, int ParentWidth, int ParentHeight)
{
	pGuiWindow->SetPosition(
		sf::Vector2f(
		static_cast<float>( ParentWidth / 2 ) - pGuiWindow->GetAllocation().width / 2.f,
		static_cast<float>( ParentHeight / 2 ) - pGuiWindow->GetAllocation().height / 2.f
		)
		);
}

void Gui::MessageBox(const std::string& Caption, const std::string& Message)
{
	::MessageBoxA(NULL, Message.c_str(), Caption.c_str(), MB_OK);

	/*
	sfg::Window::Ptr MessageBoxWnd = sfg::Window::Create(sfg::Window::TITLEBAR | sfg::Window::BACKGROUND);
	MessageBoxWnd->SetTitle(Caption);

	sfg::Label::Ptr MessageLabel(sfg::Label::Create(Message));
	sfg::Button::Ptr OkButton(sfg::Button::Create("Ok"));

	OkButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&Gui::RemoveMessageBox, this);

	MessageLabel->SetId(Message);

	sfg::Box::Ptr Layout(sfg::Box::Create(sfg::Box::VERTICAL, 5.0f));
	Layout->Pack(MessageLabel, false);
	Layout->Pack(OkButton, false);

	MessageBoxWnd->Add(Layout);

	AddWindow(MessageBoxWnd);

	Gui::PlaceToCenter(MessageBoxWnd, m_pSettings->GetRenderWindowWidth(), m_pSettings->GetRenderWindowHeight());
	*/
}

void Gui::RemoveMessageBox()
{
	sfg::Widget::Ptr Widget( sfg::Context::Get().GetActiveWidget() );

	while( Widget->GetName() != "Window" ) 
	{
		Widget = Widget->GetParent();
	}

	m_Desktop.Remove( Widget );
}

void Gui::Reset()
{
	m_Desktop.RemoveAll();
}

}