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

		m_Font.Init(sw, sh);
	}

	void RenderSystem::v_Update()
	{
		
	}

	void RenderSystem::v_Render()
	{
		static const GLfloat black[] ={0.0f, 0.0f, 0.0f, 1.0f };
		static const GLfloat one[] ={ 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);
		glClearBufferfv(GL_DEPTH, 0, one);

		m_Font.Render("Fps:", 10, 610, 0.8f, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	void RenderSystem::v_Shutdown()
	{
		m_Font.Shutdown();
	}
}