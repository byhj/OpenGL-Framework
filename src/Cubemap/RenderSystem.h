#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ogl/App.h"
#include "ogl/camera.h"

#include "cubemap.h"

namespace byhj
{

class RenderSystem : public ogl::App
{
public:
	RenderSystem() {}
	~RenderSystem() {}

	///////////////////////// Triangle and Render //////////////////////////////////
	void v_InitInfo();
	void v_Init();
	void v_Update();
	void v_Render();
	void v_Shutdown();

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void v_Movement(GLFWwindow *Triangle);
	void v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode);
	void v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset);


private:

	byhj::Skybox m_Skybox;
	ogl::Camera m_Camera;
};


}

#endif