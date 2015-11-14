#ifndef MeshLoad_H
#define MeshLoad_H


#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ogl/Shader.h"
#include "ogl/Model.h"
#include "RotationGUI.h"

namespace byhj
{
	class MeshLoad
	{
	public:

		void Init(int sw, int sh);
		void Update(const glm::mat4 &viewMat);
		void Render();
        void Shutdown();

	private:
		void init_buffer();
		void init_shader();

		struct UniformLoc
		{
			GLuint model;
		    GLuint view;
			GLuint proj;
		}uniform_loc;

		GLfloat m_Aspect = 1.0f;
		ogl::Shader m_MeshLoadShader;
		ogl::Model m_Model;
		RotationGUI m_RotationGUI;

		GLuint m_Program;
	};
}
#endif