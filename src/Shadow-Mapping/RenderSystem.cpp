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
	m_Shadow.Init(windowInfo.Width, windowInfo.Height);
	//m_DebugWindow.Init(windowInfo.Width, windowInfo.Height);
}

void RenderSystem::v_Update()
{

}

void RenderSystem::v_Render()
{

	static const GLfloat black[] = { 0.0f, 0.3f, 0.4f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, &black[0]);
	
	m_Shadow.Render();

	//glClearBufferfv(GL_COLOR, 0, &black[0]);
	//m_DebugWindow.Render(m_Shadow.GetDepthMap());

}

void RenderSystem::v_Shutdown()
{

}

}