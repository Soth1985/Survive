#include <Survive/settings.h>

namespace Survive
{

Settings::Settings()
	:
m_Score(0),
m_RenderWindowWidth(800),
m_RenderWindowHeight(600),
#ifdef _DEBUG
m_MaxMonsterC(100)
#else
m_MaxMonsterC(1000)
#endif
{

}

}