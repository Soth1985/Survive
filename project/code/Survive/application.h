#pragma once

#include <Survive/forward.h>

namespace Survive
{

class Application
{
public:

	Application();

	~Application();

	void Run();

	void ProcessEvents();

	void Update(float dt);

	void Render();

private:

	void Init();

	enum WorldID
	{
		CurrentWorld,
		LoadingWorld,
		WorldCount
	};

	std::unique_ptr<sf::RenderWindow> m_pRenderWindow;
	float m_UpdateFrequency;
	std::array<WorldPtr, WorldCount> m_Worlds;
};

}