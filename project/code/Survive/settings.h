#pragma once

#include <Survive/forward.h>

namespace Survive
{

class Settings
{
public:

	Settings();

	int GetRenderWindowHeight()const
	{
		return m_RenderWindowHeight;
	}

	int GetRenderWindowWidth()const
	{
		return m_RenderWindowWidth;
	}

private:

	int m_RenderWindowHeight;
	int m_RenderWindowWidth;
};

}