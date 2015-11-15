#include "cubemap.h"
#include "ogl/TextureManager.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace byhj
{
#pragma region VertexData

	const static GLfloat VertexData[] = {
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f

	};

#pragma endregion

	void Skybox::Init()
	{
	
		init_shader();
		init_buffer();
		init_vertexArray();
		init_texture();

		m_Model.LoadModel("armadillo.obj");
	}

	void Skybox::Render(const const ogl::MvpMatrix &matrix)
	{
		glUseProgram(program);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture); 

	// Remove any translation component of the view matrix
		glm::mat4 view  = glm::mat4( glm::mat3(matrix.view) );
		glm::mat4 proj  = matrix.proj;
		glm::mat4 model = matrix.model;

		glUniformMatrix4fv(view_loc, 1, GL_FALSE,  &view[0][0]);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE,  &proj[0][0]);
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);

		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);


		//////////////////////////////////////////////////////////////
		glUseProgram(0);

		glUseProgram(model_prog);

		glDepthFunc(GL_LESS); // Set depth function back to default
		GLfloat time = glfwGetTime();

		//model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelUniform_loc.model, 1, GL_FALSE, &matrix.view[0][0]);
		glUniformMatrix4fv(modelUniform_loc.view,  1, GL_FALSE, &proj[0][0]);
		glUniformMatrix4fv(modelUniform_loc.proj,  1, GL_FALSE, &model[0][0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
		glUniform1i(modelUniform_loc.cubemap, 0);

		m_Model.Draw(model_prog);

		glUseProgram(0);
	}

	void Skybox::Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Skybox::init_shader()
	{
		SkyboxShader.init();
		SkyboxShader.attach(GL_VERTEX_SHADER,  "Skybox.vert");
		SkyboxShader.attach(GL_FRAGMENT_SHADER, "Skybox.frag");
		SkyboxShader.link();
		SkyboxShader.info();

		program = SkyboxShader.GetProgram();
		model_loc = glGetUniformLocation(program, "model");
		view_loc  = glGetUniformLocation(program, "view");
		proj_loc  = glGetUniformLocation(program, "proj");
		tex_loc   = glGetUniformLocation(program, "skybox");

		///////////////////////////////////////////////////////
		ModelShader.init();
		ModelShader.attach(GL_VERTEX_SHADER, "model.vert");
		ModelShader.attach(GL_FRAGMENT_SHADER, "model.frag");
		ModelShader.link();
		ModelShader.info();

		model_prog = ModelShader.GetProgram();
		modelUniform_loc.model = glGetUniformLocation(model_prog, "u_Model");
		modelUniform_loc.view  = glGetUniformLocation(model_prog, "u_View");
		modelUniform_loc.proj  = glGetUniformLocation(model_prog, "u_Proj");
		modelUniform_loc.viewPos = glGetUniformLocation(model_prog, "u_ViewPos");
		modelUniform_loc.cubemap = glGetUniformLocation(model_prog, "u_Cubemap");

	}

	void Skybox::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Skybox::init_vertexArray()
	{	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 3, (GLvoid*)(NULL));

		glBindVertexArray(0);
	}

	void Skybox::init_texture()
	{
		m_TextureMgr.Init();
	
		// Cubemap (Skybox)
		std::vector<std::string> faces;
		faces.push_back("/house/posx.jpg");
		faces.push_back("/house/negx.jpg");
		faces.push_back("/house/posy.jpg");
		faces.push_back("/house/negy.jpg");
		faces.push_back("/house/posz.jpg");
		faces.push_back("/house/negz.jpg");

		cubemap_texture = m_TextureMgr.LoadTexture(faces);


		
	}



}//Namespace