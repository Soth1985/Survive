#include <Survive/context.h>
#include <Survive/gui.h>
#include <Survive/world.h>
#include <Survive/content_manager.h>

namespace Survive
{

Context::Context()
	:
m_pWindow(0)
{

}

Context::~Context()
{

}

sf::RenderWindow* Context::GetRenderWindow()
{
	return m_pWindow;
}

void Context::SetRenderWindow(sf::RenderWindow* pWindow)
{
	m_pWindow = pWindow;
}

ContentManager* Context::GetContentManager()
{
	return m_pContentManager.get();
}

void Context::SetContentManager(ContentManager* pManager)
{
	m_pContentManager.reset(pManager);
}

Gui* Context::GetGui()
{
	return m_pGui.get();
}

void Context::SetGui(Gui* pGui)
{
	m_pGui.reset(pGui);
}

World* Context::GetWorld()
{
	return m_pWorld.get();
}

void Context::SetWorld(World* pWorld)
{
	m_pWorld.reset(pWorld);
}

}