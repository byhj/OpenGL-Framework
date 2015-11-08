#ifndef TessTriangle_H
#define TessTriangle_H


#include "ogl/Shader.h"
#include "ogl/Debug.h"
#include <glfw/glfw3.h>
#include "TessGUI.h"

namespace byhj
{


	class TessTriangle
	{
	public:
		TessTriangle()	 = default;
		~TessTriangle()	 = default;

		void Init(int sw, int sh);
		void Render();
		void Update();
		void Shutdown();

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();

		struct UniformLoc
		{
			GLuint model;
			GLuint view;
			GLuint proj;
			GLuint lightDir;
			GLuint diffuse;
			GLuint ambient;
			GLuint tessInner;
			GLuint tessOuter;
		}uniform_loc;

		ogl::Shader TessShader = {"TessTrianglerShader"};
		ogl::Debug  m_Debug;

		GLuint vao, vbo, ibo;
		GLuint program;
		GLuint sw, sh;
		TessGUI m_TessGUI;
};

}
#endif