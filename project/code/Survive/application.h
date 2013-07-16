#pragma once

#include <SFML/Graphics.hpp>

namespace Survive
{

class Application
{
public:

	Application();

	void Run();

private:

	sf::RenderWindow m_RenderWindow;
};

}