#include <Survive/application.h>
#include <Survive/world.h>
#include <Survive/context.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/main_menu_state.h>
#include <Survive/game_state.h>
#include <SFML/Graphics.hpp>

namespace Survive
{

Application::Application()
	:
m_pRenderWindow(new sf::RenderWindow(sf::VideoMode(800, 600), "Survive", sf::Style::Close)),
m_pContext(new Context()),
m_StateStack(m_pContext.get()),
m_UpdateFrequency(1.0f / 60.0f)
{
	m_pContext->SetRenderWindow(m_pRenderWindow.get());
	m_pContext->SetContentManager(new ContentManager());
	m_pContext->SetGui(new Gui());
	//m_pContext->SetWorld(new World(m_pContext.get()));

	m_StateStack.RegisterState<MainMenuState>(eStateID::MainMenu);
	m_StateStack.RegisterState<GameState>(eStateID::Game);

	m_StateStack.PushState(eStateID::MainMenu);
}

Application::~Application()
{

}

void Application::ProcessEvents()
{
	sf::Event Event;

	while (m_pRenderWindow->pollEvent(Event))
	{
		m_StateStack.HandleEvent(Event);

		if (Event.type == sf::Event::Closed)
			m_pRenderWindow->close();
	}
}

void Application::Update(float Dt)
{
	m_StateStack.Update(Dt);
}

void Application::Render()
{
	m_pRenderWindow->clear();

	m_StateStack.Draw();

	m_pRenderWindow->display();
}

void Application::Init()
{
	
}

void Application::Run()
{
	sf::Clock Clocks;
	sf::Time PrevUpdateTime = sf::Time::Zero;
	sf::Time UpdateFrequency = sf::seconds(m_UpdateFrequency);

	Init();

	while (m_pRenderWindow->isOpen())
	{
		sf::Time Dt = Clocks.restart();
		PrevUpdateTime += Dt;

		while (PrevUpdateTime > UpdateFrequency)
		{
			PrevUpdateTime -= UpdateFrequency;

			ProcessEvents();
			Update(UpdateFrequency.asSeconds());
		}

		Render();
	}
}

}