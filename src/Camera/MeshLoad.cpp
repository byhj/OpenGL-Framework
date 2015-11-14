#include "MeshLoad.h"

namespace byhj
{
	void MeshLoad::Init(int sw, int sh)
	{
		m_RotationGUI.v_Init(sw, sh);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		m_Aspect = static_cast<GLfloat>(sw) / sh;

		init_buffer();
		init_shader();
	}

	void MeshLoad::Update()
	{

		glUseProgram(m_Program);

	    GLfloat time = glfwGetTime();

		glm::mat4 model = m_RotationGUI.GetRotationMat(); 
		glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.2f, 5.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) );
		glm::mat4 proj  = glm::perspective(45.0f, m_Aspect, 0.1f, 1000.0f);

		glUniformMatrix4fv(uniform_loc.model, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(uniform_loc.view, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(uniform_loc.proj, 1, GL_FALSE, &proj[0][0]);

		glUseProgram(0);
	}

	void MeshLoad::Render()
	{
		glUseProgram(m_Program);

		m_Model.Draw(m_Program);

		glUseProgram(0);

		m_RotationGUI.v_Render();
	}

	void MeshLoad::Shutdown()
	{
		m_RotationGUI.v_Shutdown();
	}

	void MeshLoad::init_buffer()
	{
		m_Model.LoadModel("armadillo.obj");
	}


	void MeshLoad::init_shader()
	{
		m_MeshLoadShader.init();
		m_MeshLoadShader.attach(GL_VERTEX_SHADER, "model.vert");
		m_MeshLoadShader.attach(GL_FRAGMENT_SHADER, "model.frag");
		m_MeshLoadShader.link();
		m_MeshLoadShader.info();

		m_Program = m_MeshLoadShader.GetProgram();
		uniform_loc.model = glGetUniformLocation(m_Program, "u_Model");
		uniform_loc.view  = glGetUniformLocation(m_Program, "u_View");
		uniform_loc.proj  = glGetUniformLocation(m_Program, "u_Proj");
		
	}
}
