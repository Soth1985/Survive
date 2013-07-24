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

	int GetMaxMonsterC()const
	{
		return m_MaxMonsterC;
	}

	int GetScore()const
	{
		return m_Score;
	}

	void SetScore(int Score)
	{
		m_Score = Score;
	}

private:

	int m_RenderWindowHeight;
	int m_RenderWindowWidth;
	int m_MaxMonsterC;
	int m_Score;
};

}