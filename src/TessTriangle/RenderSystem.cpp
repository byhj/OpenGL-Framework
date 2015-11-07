#include "RenderSystem.h"

namespace byhj
{
	void RenderSystem::v_InitInfo()
	{
		windowInfo.title += "Tess Triangle";
	}

	void RenderSystem::v_Init()
	{
		auto sw = GetScreenWidth();
		auto sh = GetScreenHeight();

		m_TessTriangle.Init(sw, sh);
	}

	void RenderSystem::v_Update()
	{
		m_TessTriangle.Update();
	}

	void RenderSystem::v_Render()
	{
		static const GLfloat black[] ={ 0.0f, 0.0f, 0.0f, 1.0f };
		static const GLfloat one[] ={ 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);
		glClearBufferfv(GL_DEPTH, 0, one);

		m_TessTriangle.Render();
	}

	void RenderSystem::v_Shutdown()
	{
		m_TessTriangle.Shutdown();
	}
}