#include <Survive/context.h>
#include <Survive/gui.h>
#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <Survive/settings.h>
#include <Survive/debug_render.h>

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

Settings* Context::GetSettings()
{
	return m_pSettings.get();
}

void Context::SetSettings(Settings* pSettings)
{
	m_pSettings.reset(pSettings);
}

DebugRender* Context::GetDebugRender()
{
	return m_pDebugRender.get();
}

void Context::SetDebugRender(DebugRender* pRender)
{
	m_pDebugRender.reset(pRender);
}

}