#include <Survive/game_over_state.h>
#include <Survive/context.h>
#include <Survive/settings.h>
#include <Survive/content_manager.h>
#include <Survive/string_utilities.h>
#include <Survive/gui.h>

namespace Survive
{

GameOverState::GameOverState(StateStack* pStack, Context* pContext)
	:
State(pStack, pContext)
{
	sf::Texture* BackGroundTex = pContext->GetContentManager()->LoadTexture(eTextureID::GameOverBackground);
	m_Background.setTexture(*BackGroundTex);
	sf::FloatRect Bounds = m_Background.getLocalBounds();
	sf::Vector2u WindowSize = pContext->GetRenderWindow()->getSize();
	sf::Vector2f Scale(WindowSize.x / Bounds.width, WindowSize.y / Bounds.height);
	m_Background.setScale(Scale);

	const sf::Font* pFont = pContext->GetContentManager()->Fonts().Get(eFontID::Arial);
	char Buf[32];
	StringUtilities::ToString(pContext->GetSettings()->GetScore(), Buf, 31);
	std::string Message("Your score is ");
	Message = Message + Buf + "\nPress Any Key To Continue";
	m_Text.setFont(*pFont);
	m_Text.setCharacterSize(20);
	m_Text.setString(Message);
	
	sf::FloatRect TextBounds = m_Text.getLocalBounds();

	m_Text.setPosition(
		sf::Vector2f(
		static_cast<float>( pContext->GetSettings()->GetRenderWindowWidth() / 2 ) - TextBounds.width / 2.f,
		static_cast<float>( pContext->GetSettings()->GetRenderWindowHeight() / 2 ) - TextBounds.height / 2.f - 200.0f
		)
		);
}

GameOverState::~GameOverState()
{
	
}

void GameOverState::Draw()
{
	GetContext()->GetRenderWindow()->draw(m_Background);
	GetContext()->GetRenderWindow()->draw(m_Text);
}

bool GameOverState::Update(float Dt)
{
	return false;
}

bool GameOverState::HandleEvent(const sf::Event& Event)
{	
	if (Event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		RequestStackPush(eStateID::MainMenu);
	}

	return false;
}

}