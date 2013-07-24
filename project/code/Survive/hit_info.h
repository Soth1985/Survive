#pragma once

#include <Survive/forward.h>

namespace Survive
{

struct HitInfo
{
	HitInfo()
		:
	m_pObject(0),
	m_Param(0.0f)
	{

	}

	HitInfo(SceneNode* pObject, float Param = FLT_MAX)
		:
	m_pObject(pObject),
	m_Param(Param)
	{

	}

	SceneNode* m_pObject;
	float m_Param;
};

}