#pragma once

#include <Survive/forward.h>

namespace Survive
{

struct HitInfo
{
	HitInfo()
		:
	m_Object(0),
	m_Param(0.0f)
	{

	}

	HitInfo(SceneNode* Object, float Param = FLT_MAX)
		:
	m_Object(Object),
	m_Param(Param)
	{

	}

	SceneNode* m_Object;
	float m_Param;
};

}