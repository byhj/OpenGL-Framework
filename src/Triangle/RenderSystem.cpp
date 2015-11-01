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
	myGui.Init(windowInfo.Width, windowInfo.Height);
	m_Triangle.Init();
}

void RenderSystem::v_Render()
{

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 bgColor = myGui.GetColor();
	glClearBufferfv(GL_COLOR, 0, &bgColor[0]);

	if (myGui.GetRenderMode())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_Triangle.Render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	myGui.Render();
}

void RenderSystem::v_Shutdown()
{
	m_Triangle.Shutdown();
	myGui.Shutdown();
}

}