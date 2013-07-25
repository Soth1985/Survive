#include <Survive/game_state.h>
#include <Survive/world.h>
#include <Survive/gui.h>
#include <Survive/context.h>
#include <Survive/debug_render.h>
#include <Survive/settings.h>
#include <Survive/scene_nodes/player_entity_node.h>
#include <Survive/string_utilities.h>

namespace Survive
{

GameState::GameState(StateStack* pStack, Context* pContext)
	:
State(pStack, pContext),
m_Paused(false)
{
	pContext->SetWorld(new World(pContext));
	pContext->GetWorld()->Init();

	//Menu
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
	//HUD
	m_pHudWindow = sfg::Window::Create(sfg::Window::NO_STYLE);

	m_pHealthLabel = sfg::Label::Create("");
	m_pScoreLabel = sfg::Label::Create("");

	sfg::Box::Ptr HudLayout(sfg::Box::Create(sfg::Box::HORIZONTAL, 5.0f));
	HudLayout->Pack(m_pHealthLabel, false);
	HudLayout->Pack(m_pScoreLabel, false);

	m_pHudWindow->Add(HudLayout);
	pContext->GetGui()->AddWindow(m_pHudWindow);
	//m_pHudWindow->Show(true);

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
			GetContext()->SetWorld(0);
			GetContext()->GetDebugRender()->Clear();
			sf::RenderWindow* pRenderWindow = GetContext()->GetRenderWindow();
			pRenderWindow->setView(pRenderWindow->getDefaultView());
		}
		else
		{
			PlayerEntityNode* pPlayer = GetContext()->GetWorld()->GetPlayer();
			char Buf[32];
			StringUtilities::ToString(pPlayer->GetHealth(), Buf, 31);
			m_pHealthLabel->SetText(std::string("Health: ") + Buf);
			StringUtilities::ToString(GetContext()->GetSettings()->GetScore(), Buf, 31);
			m_pScoreLabel->SetText(std::string("Score: ") + Buf);
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
			m_pHudWindow->Show(false);
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
	m_pHudWindow->Show(true);
	m_Paused = false;
}

void GameState::OnMenuReturnClicked()
{
	RequestStateClear();
	RequestStackPush(eStateID::MainMenu);
}

}