#include <Survive/main_menu_state.h>
#include <Survive/context.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>

namespace Survive
{

MainMenuState::MainMenuState(StateStack* pStack, Context* pContext)
	:
State(pStack, pContext)
{
	sf::Texture* BackGroundTex = pContext->GetContentManager()->LoadTexture(eTextureID::MainMenuBackground);
	m_Background.setTexture(*BackGroundTex);
	sf::FloatRect Bounds = m_Background.getGlobalBounds();
	sf::Vector2u WindowSize = pContext->GetRenderWindow()->getSize();
	sf::Vector2f Scale(WindowSize.x / Bounds.width, WindowSize.y / Bounds.height);
	m_Background.setScale(Scale);

	m_pWindow = sfg::Window::Create(sfg::Window::NO_STYLE);

	sfg::Label::Ptr WindowLabel(sfg::Label::Create("Survive"));
	sfg::Button::Ptr PlayGameButton(sfg::Button::Create("Play"));
	sfg::Button::Ptr ExitButton(sfg::Button::Create("Exit"));

	WindowLabel->SetId("main_menu_window_label");
	PlayGameButton->SetId("main_menu_play_button");
	ExitButton->SetId("main_menu_exit_button");

	// Layout.
	sfg::Box::Ptr Layout(sfg::Box::Create(sfg::Box::VERTICAL, 5.0f));
	Layout->Pack(WindowLabel, false);
	Layout->Pack(PlayGameButton, false);
	Layout->Pack(ExitButton, false);

	ExitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenuState::OnExitClicked, this);
	PlayGameButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenuState::OnPlayClicked, this);

	m_pWindow->Add(Layout);

	pContext->GetGui()->AddWindow(m_pWindow);

	pContext->GetGui()->GetDesktop().SetProperty( "Label#main_menu_window_label", "FontSize", 36.f );
	pContext->GetGui()->GetDesktop().SetProperty( "Label#main_menu_window_label", "Color", sf::Color(255, 0, 0) );
	pContext->GetGui()->GetDesktop().SetProperty( "Button#main_menu_play_button", "FontSize", 24.f );
	pContext->GetGui()->GetDesktop().SetProperty( "Button#main_menu_exit_button", "FontSize", 24.f );

	Gui::PlaceToCenter(m_pWindow, pContext->GetRenderWindow());

	pContext->GetRenderWindow()->resetGLStates();
}

MainMenuState::~MainMenuState()
{
	//GetContext()->GetGui()->RemoveWindow(m_pWindow);
	GetContext()->GetGui()->GetDesktop().RemoveAll();
}

void MainMenuState::Draw()
{
	GetContext()->GetRenderWindow()->draw(m_Background);
	GetContext()->GetGui()->Draw(GetContext()->GetRenderWindow());
}

bool MainMenuState::Update(float Dt)
{
	GetContext()->GetGui()->Update(Dt);
	return false;
}

bool MainMenuState::HandleEvent(const sf::Event& Event)
{
	GetContext()->GetGui()->HandleEvent(Event);
	return false;
}

void MainMenuState::OnExitClicked()
{
	GetContext()->GetRenderWindow()->close();
}

void MainMenuState::OnPlayClicked()
{
	RequestStackPop();
	RequestStackPush(eStateID::Game);
}

}