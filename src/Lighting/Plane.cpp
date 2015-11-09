#include "Plane.h"

#pragma region VertexData

glm::vec3 lightPositions[] =
{
	glm::vec3(-3.0f, 0.0f, 0.0f),
	glm::vec3(-1.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(3.0f, 0.0f, 0.0f)
};

glm::vec3 lightColors[] =
{
	glm::vec3(0.25),
	glm::vec3(0.50),
	glm::vec3(0.75),
	glm::vec3(1.00)
};

const static GLfloat PlaneVertex[] =
{
	// Positions          // Normals         // Texture Coords
	8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
   -8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
   -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,

	8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
   -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
	8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
};
const static GLsizei PlaneVertexSize = sizeof(PlaneVertex);

#pragma  endregion

namespace byhj
{
	void Plane::Init(int sw, int sh)
	{
		m_LightGUI.v_Init(sw, sh);
		m_TextureMgr.Init();

		aspect = static_cast<GLfloat>(sw) / sh;

		init_buffer();
		init_vertexArray();
		init_shader();
		init_texture();
	}

	void Plane::Update()
	{
		glUseProgram(program);

		//map the texture to the shader;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTex);
		glUniform1i(uniform_loc.woodTex, 0);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.5f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 proj  = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);

		glm::vec3 camPos = glm::vec3(0.0f, 0.5f, 4.0f);

		glUniformMatrix4fv(uniform_loc.model, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(uniform_loc.view, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(uniform_loc.proj, 1, GL_FALSE, &proj[0][0]);

		glUniform3fv(uniform_loc.lightPos, 4, &lightPositions[0][0]);
		glUniform3fv(uniform_loc.lightColor, 4, &lightColors[0][0]);
		glUniform3fv(uniform_loc.viewPos, 1, &camPos[0]);

		auto gamma = m_LightGUI.GetGamma();
		glUniform1i(uniform_loc.gamma, gamma);

		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &uniform_loc.lightSub[1]);

		glUseProgram(0);
	}

	void Plane::Render()
	{


		glUseProgram(program);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 6);	

		glBindVertexArray(0);
		glUseProgram(0);

		m_LightGUI.v_Render();
	}

	void Plane::Shutdown()
	{
		m_LightGUI.v_Shutdown();
	}

	void Plane::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, PlaneVertexSize, PlaneVertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glGenBuffers(1, &ibo);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, );
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void Plane::init_vertexArray()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Plane::init_shader()
	{
		m_PlaneShader.init();
		m_PlaneShader.attach(GL_VERTEX_SHADER, "light.vert");
		m_PlaneShader.attach(GL_FRAGMENT_SHADER, "light.frag");
		m_PlaneShader.link();
		m_PlaneShader.info();


		uniform_loc.lightSub[0]  = -1;		uniform_loc.lightSub[1]  = -1;
		program = m_PlaneShader.GetProgram();
		uniform_loc.woodTex = glGetUniformLocation(program, "u_WoodTex");
		uniform_loc.lightSub[0] = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "Phong");
		uniform_loc.lightSub[1] = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "BlinnPhong");
		uniform_loc.lightModelSub = glGetSubroutineUniformLocation(program, GL_FRAGMENT_SHADER, "lightModelUniform");

		uniform_loc.model = glGetUniformLocation(program, "u_Model");
		uniform_loc.view  = glGetUniformLocation(program, "u_View");
		uniform_loc.proj  = glGetUniformLocation(program, "u_Proj");
		uniform_loc.gamma = glGetUniformLocation(program, "u_Gamma");
		uniform_loc.lightPos =    glGetUniformLocation(program, "u_LightPos");
		uniform_loc.lightColor = 	glGetUniformLocation(program, "u_LightColor");
		uniform_loc.viewPos = 	glGetUniformLocation(program, "u_ViewPos");
	}

	void Plane::init_texture()
	{
		m_TextureMgr.LoadTexture("wood.png");
		woodTex = m_TextureMgr.GetTexID("wood.png");
	}


}