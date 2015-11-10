#ifndef Geometry_H
#define Geometry_H

#include <GL/glew.h>
#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "Polygon.h"

namespace byhj
{

class Geometry
{
public:
	Geometry();
	~Geometry();

	void Init();
	void Render();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();

	byhj::MeshData m_MeshData;
	byhj::Polygon m_Polygon;

	ogl::Shader GeometryShader{ "Geometry Shader" };
	GLuint program = 0;
	GLuint vbo, ibo, vao;
};

}
#endif
