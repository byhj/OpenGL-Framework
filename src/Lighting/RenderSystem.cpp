#include "RenderSystem.h"

namespace byhj
{
	void RenderSystem::v_InitInfo()
	{
		windowInfo.title += "Lighting";
	}

	void RenderSystem::v_Init()
	{
		auto sw = GetScreenWidth();
		auto sh = GetScreenHeight();

		m_Plane.Init(sw, sh);
	}

	void RenderSystem::v_Update()
	{
		m_Plane.Update();
	}

	void RenderSystem::v_Render()
	{
		static const GLfloat bgColor[] ={ 0.2f, 0.3f, 0.4f, 1.0f };
		static const GLfloat one[] ={ 1.0f };

		glClearBufferfv(GL_COLOR, 0, bgColor);
		glClearBufferfv(GL_DEPTH, 0, one);

		m_Plane.Render();
	}

	void RenderSystem::v_Shutdown()
	{
		m_Plane.Shutdown();
	}
}