#include <GL/glew.h>
#include "RenderSystem.h"

namespace byhj
{

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::v_InitInfo()
{
	windowInfo.title += "Triangle";
}

void RenderSystem::v_Init()
{
	m_MeshLoad.Init(windowInfo.Width, windowInfo.Height);
}

void RenderSystem::v_Update()
{
	static GLfloat lastFrame = static_cast<float>(glfwGetTime());
	GLfloat currentFrame = static_cast<float>(glfwGetTime());
	GLfloat deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	m_Camera.update(deltaTime);

	m_MeshLoad.Update(m_Camera.GetViewMatrix());
}

void RenderSystem::v_Render()
{

	static const GLfloat black[] = { 0.2f, 0.3f, 0.4f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	static const GLfloat one[] = {1.0f};
	glClearBufferfv(GL_DEPTH, 0, one);

	m_MeshLoad.Render();

}

void RenderSystem::v_Shutdown()
{
	m_MeshLoad.Shutdown();
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