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
	m_Grass.Init();
}

void RenderSystem::v_Update()
{
	m_Grass.Update();
}

void RenderSystem::v_Render()
{

	static const GLfloat black[] = { 0.2f, 0.3f, 0.4f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, &black[0]);

	m_Grass.Render();

}

void RenderSystem::v_Shutdown()
{
	m_Grass.Shutdown();
}

}