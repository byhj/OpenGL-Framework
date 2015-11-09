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
		m_TessTriangle.Init(sw, sh);
	}

	void RenderSystem::v_Update()
	{
		countFps();

		m_TessTriangle.Update();
	}

	void RenderSystem::v_Render()
	{
		static const GLfloat black[] ={0.0f, 0.0f, 0.0f, 1.0f };
		static const GLfloat one[] ={ 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);
		glClearBufferfv(GL_DEPTH, 0, one);

		m_Font.Render("Graphics card: " + GetGLRenderer(), 10, windowInfo.Height - 20);
		m_Font.Render("GL Version: " + GetGLVersion(), 10, windowInfo.Height - 40);
		m_Font.Render("GLSL Version: " + GetGLSLVersion(), 10, windowInfo.Height - 60);
		m_Font.Render("FPS: " + std::to_string(m_Fps), 10, 30);

		m_TessTriangle.Render();
	}

	void RenderSystem::v_Shutdown()
	{
		m_TessTriangle.Shutdown();
	}


	void RenderSystem::countFps()
	{
		static float currTime = glfwGetTime();
		static float lastTime = glfwGetTime();
		static float Time = 0.0f;

		currTime = glfwGetTime();
		Time += currTime - lastTime;

		static int cnt = 0;
		if (Time >= 1.0f)
		{
			m_Fps = cnt;
			cnt = 0;
			Time = 0.0f;
		}
		++cnt;
		lastTime = currTime;
	}
}