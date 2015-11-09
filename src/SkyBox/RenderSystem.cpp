#include "RenderSystem.h"

const static glm::vec3 g_LightPos(1.5f, 0.5f, 0.0f);

namespace byhj
{
	void RenderSystem::v_InitInfo()
	{
		windowInfo.title += ": Cube";
	}

	void RenderSystem::v_Init()
	{
		m_TessGUI.v_Init(windowInfo.Width, windowInfo.Height);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	

		m_Skybox.Init();
		m_Camera.SetPos( glm::vec3(0.0f, 1.0f, 3.0f) );
	}

	void RenderSystem::v_Update()
	{
		static GLfloat lastFrame = static_cast<float>(glfwGetTime());
		GLfloat currentFrame = static_cast<float>(glfwGetTime());
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Camera.update(deltaTime);
	}

	void RenderSystem::v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.4f, 0.5f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		static ogl::MvpMatrix matrix;
		matrix.view  = m_Camera.GetViewMatrix();
		matrix.proj  = glm::perspective(m_Camera.GetZoom(), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::mat4(1.0f);

		// Draw skybox first, disable depth writing. 
		// This way the skybox will always be drawn at the background of all the other objects.
		glDepthMask(GL_FALSE);

		m_Skybox.Render(matrix);

		glDepthMask(GL_TRUE);
		//glDepthFunc(GL_LESS); // Set depth function back to default
		m_TessGUI.v_Render();

	}

	void RenderSystem::v_Shutdown()
	{
		m_Skybox.Shutdown();
	}

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void RenderSystem::v_Movement(GLFWwindow *Triangle)
	{
		m_Camera.movement(Triangle);
	}
	void RenderSystem::v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode)
	{
		m_Camera.key_callback(Triangle, key, scancode, action, mode);
	}

	void RenderSystem::v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos)
	{
		m_Camera.mouse_callback(Triangle, xpos, ypos);
	}

	void RenderSystem::v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset)
	{
		m_Camera.scroll_callback(Triangle, xoffset, yoffset);
	}


}