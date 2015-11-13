#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ogl/App.h"
#include "Shadow.h"
#include "DebugWindow.h"

namespace byhj
{

class RenderSystem : public ogl::App
{
public:
	RenderSystem();
	~RenderSystem();

public:
	void v_InitInfo();
	void v_Init();
	void v_Update();
	void v_Render();
	void v_Shutdown();

private:
	Shadow m_Shadow;
	DebugWindow m_DebugWindow;
};

}

#endif