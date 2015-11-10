#ifndef Plane_H
#define Plane_H

#include <GL/glew.h>
#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "ogl/Polygon.h"

namespace byhj
{

class Plane
{
public:
	Plane();
	~Plane();

	void Init();
	void Render();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();

	ogl::MeshData m_PlaneMeshData;
	ogl::Polygon m_Polygon;

	ogl::Shader PlaneShader{ "Plane Shader" };
	GLuint program = 0;
	GLuint vbo, ibo, vao;
};

}
#endif
