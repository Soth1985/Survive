#include <Survive/game_state.h>
#include <Survive/world.h>
#include <Survive/gui.h>
#include <Survive/context.h>
#include <Survive/debug_render.h>
#include <Survive/scene_nodes/player_entity_node.h>

namespace Survive
{

GameState::GameState(StateStack* pStack, Context* pContext)
	:
State(pStack, pContext),
m_Paused(false)
{
	pContext->SetWorld(new World(pContext));
	pContext->GetWorld()->Init();

	m_pMenuWindow = sfg::Window::Create(sfg::Window::NO_STYLE);

	sfg::Label::Ptr WindowLabel(sfg::Label::Create("Menu"));
	sfg::Button::Ptr ResumeButton(sfg::Button::Create("Resume Game"));
	sfg::Button::Ptr ReturnButton(sfg::Button::Create("Return To Main Menu"));

	WindowLabel->SetId("game_menu_window_label");
	ResumeButton->SetId("game_menu_resume_button");
	ReturnButton->SetId("game_menu_return_button");

	sfg::Box::Ptr Layout(sfg::Box::Create(sfg::Box::VERTICAL, 5.0f));
	Layout->Pack(WindowLabel, false);
	Layout->Pack(ResumeButton, false);
	Layout->Pack(ReturnButton, false);

	ResumeButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&GameState::OnMenuResumeClicked, this);
	ReturnButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&GameState::OnMenuReturnClicked, this);

	m_pMenuWindow->Add(Layout);

	pContext->GetGui()->AddWindow(m_pMenuWindow);

	pContext->GetGui()->GetDesktop().SetProperty( "Label#game_menu_window_label", "FontSize", 36.f );
	pContext->GetGui()->GetDesktop().SetProperty( "Button#game_menu_resume_button", "FontSize", 24.f );
	pContext->GetGui()->GetDesktop().SetProperty( "Button#game_menu_return_button", "FontSize", 24.f );

	Gui::PlaceToCenter(m_pMenuWindow, pContext->GetRenderWindow()->getSize().x, pContext->GetRenderWindow()->getSize().y);

	m_pMenuWindow->Show(false);

	pContext->GetRenderWindow()->resetGLStates();
}

GameState::~GameState()
{
	GetContext()->GetGui()->Reset();
}

void GameState::Draw()
{
	GetContext()->GetWorld()->Draw(GetContext()->GetRenderWindow());

	GetContext()->GetGui()->Draw(GetContext()->GetRenderWindow());
}

bool GameState::Update(float Dt)
{
	if (!m_Paused)
	{
		GetContext()->GetWorld()->Update(Dt);

		if (GetContext()->GetWorld()->GetPlayer()->GetHealth() <= 0)
		{
			RequestStackPop();
			RequestStackPush(eStateID::GameOver);
		}
	}

	GetContext()->GetGui()->Update(Dt);
	
	return false;
}

bool GameState::HandleEvent(const sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
		{
			m_Paused = true;
			m_pMenuWindow->Show(true);
		}

		if (Event.key.code == sf::Keyboard::F2)
		{
			GetContext()->GetDebugRender()->SetEnabled(!GetContext()->GetDebugRender()->GetEnabled());
		}
	}

	GetContext()->GetGui()->HandleEvent(Event);
	return false;
}

void GameState::OnMenuResumeClicked()
{
	m_pMenuWindow->Show(false);
	m_Paused = false;
}

void GameState::OnMenuReturnClicked()
{
	RequestStateClear();
	RequestStackPush(eStateID::MainMenu);
}

}