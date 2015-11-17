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
	m_Scene.Init(windowInfo.Width, windowInfo.Height);
}

void RenderSystem::v_Update()
{
	m_Scene.Update();
}

void RenderSystem::v_Render()
{

	static const GLfloat black[] = { 0.2f, 0.3f, 0.4f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	static const GLfloat one[] = {1.0f};
	glClearBufferfv(GL_DEPTH, 0, one);

	m_Scene.Render();

}

void RenderSystem::v_Shutdown()
{
	m_Scene.Shutdown();
}

}