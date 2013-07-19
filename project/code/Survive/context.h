#pragma once

#include <Survive/forward.h>

namespace Survive
{

class Context
{
public:

	Context();

	~Context();

	sf::RenderWindow* GetRenderWindow();

	void SetRenderWindow(sf::RenderWindow* pWindow);

	ContentManager* GetContentManager();

	void SetContentManager(ContentManager* pManager);

	Gui* GetGui();

	void SetGui(Gui* pGui);

	World* GetWorld();

	void SetWorld(World* pWorld);

private:
	
	sf::RenderWindow* m_pWindow;
	ContentManagerPtr m_pContentManager;
	GuiPtr m_pGui;
	WorldPtr m_pWorld;
};

}