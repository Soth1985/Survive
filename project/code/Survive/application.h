#pragma once

#include <Survive/forward.h>
#include <Survive/state_stack.h>

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

	std::unique_ptr<sf::RenderWindow> m_pRenderWindow;
	ContextPtr m_pContext;
	StateStack m_StateStack;
	float m_UpdateFrequency;
};

}