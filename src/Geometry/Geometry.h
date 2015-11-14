#ifndef Geometry_H
#define Geometry_H

#include <GL/glew.h>
#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "Polygon.h"
#include <glfw/glfw3.h>
namespace byhj
{

class Geometry
{
public:
	Geometry();
	~Geometry();

	void Init(int sw, int sh);
	void Update();
	void Render();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();

	byhj::MeshData m_MeshData;
	byhj::Polygon m_Polygon;

	GLfloat m_Aspect = 1.0f;
	struct UniformLoc 
	{
		GLuint model;
		GLuint view;
		GLuint proj;
	}uniform_loc;

	ogl::Shader GeometryShader{ "Geometry Shader" };
	GLuint m_Program = 0;
	GLuint vbo, ibo, vao;
};

}
#endif
