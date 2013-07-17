#include <Survive/application.h>
#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <SFML/Graphics.hpp>

namespace Survive
{

Application::Application()
	:
m_pRenderWindow(new sf::RenderWindow(sf::VideoMode(800, 600), "Survive", sf::Style::Close)),
m_UpdateFrequency(1.0f / 60.0f)
{
	m_Worlds[CurrentWorld].reset(new World());
}

Application::~Application()
{

}

void Application::ProcessEvents()
{
	sf::Event event;

	while (m_pRenderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_pRenderWindow->close();
	}
}

void Application::Update(float Dt)
{
	m_Worlds[CurrentWorld]->Update(Dt);
}

void Application::Render()
{
	m_pRenderWindow->clear();

	m_Worlds[CurrentWorld]->Draw(m_pRenderWindow.get());

	m_pRenderWindow->display();
}

void Application::Init()
{
	m_Worlds[CurrentWorld]->GetContentManager()->LoadBigTexture(eBigTextureID::Landscape, "Textures/Map3.jpg");
	m_Worlds[CurrentWorld]->Init(m_pRenderWindow->getDefaultView());
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