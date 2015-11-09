#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ogl/App.h"
#include "Triangle.h"
#include "Audio.h"

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
	byhj::Triangle m_Triangle;
	byhj::Audio    m_Audio;

};

}

#endif