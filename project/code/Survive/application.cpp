#include <Survive/Application.h>

namespace Survive
{

Application::Application()
	:
m_RenderWindow(sf::VideoMode(1024, 768), "Survive", sf::Style::Close)
{

}

void Application::Run()
{
	while (m_RenderWindow.isOpen())
	{
		sf::Event event;

		while (m_RenderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_RenderWindow.close();
		}
	}
}

}