#ifndef DebugWindow_H
#define DebugWindow_H

#include "ogl/Shader.h"

namespace byhj
{

class DebugWindow
{
public:
	DebugWindow() = default;
	~DebugWindow() = default;

	void Init(int depthWidth, int depthHeight);
	void Render(GLuint texID);
	void Update();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();
	
	ogl::Shader m_DebugShader;
	GLuint m_Program;
	GLuint vao, vbo, ibo;
	GLfloat sw, sh;
	GLuint shadowTex_loc;

};

}
#endif