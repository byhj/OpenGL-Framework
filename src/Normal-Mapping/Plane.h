#ifndef Plane_H
#define Plane_H

#include <GL/glew.h>
#include "ogl/Shader.h"
#include "ogl/Utility.h"
#include "ogl/Polygon.h"
#include  "ogl/texture.h"

namespace byhj
{

class Plane
{
public:
	Plane();
	~Plane();

	void Init(int sw, int sh);
	void Render();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();
	void init_texture();

	struct UniformLoc
	{
		GLuint model;
		GLuint view;
		GLuint proj;
		GLuint colorTex;
		GLuint normalTex;
	}uniform_loc;

	ogl::MeshData m_PlaneMeshData;
	ogl::Polygon m_Polygon;
	ogl::Shader PlaneShader{ "Plane Shader" };

	GLuint colorTex, normalTex;
	GLfloat m_Aspect = 1.0f;
	GLuint program = 0;
	GLuint vbo, ibo, vao;
};

}
#endif
