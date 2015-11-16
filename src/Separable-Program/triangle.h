#ifndef Triangle_H
#define Triangle_H

#include <GL/glew.h>
#include "ogl/Shader.h"

namespace byhj
{

class Triangle
{
public:
	Triangle();
	~Triangle();

	void Init();
	void Render(float aspect);
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();

	GLuint vert_prog = 0;
	GLuint frag_prog = 0;
	GLuint pipeline  = 0;
	GLuint mvp_loc   = 0;
	GLuint color_loc = 0;
};

}
#endif
