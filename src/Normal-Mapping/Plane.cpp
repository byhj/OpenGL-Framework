#include "Plane.h"

namespace byhj
{

Plane::Plane()
{

}

Plane::~Plane()
{

}

void Plane::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
	init_texture();
}

void Plane::Render()
{
	//Use this shader and vao data to render
	glUseProgram(program);

	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glUniform1i(uniform_loc.colorTex, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glUniform1i(uniform_loc.normalTex, 1);

	//float currentTime = static_cast<float>(glfwGetTime());
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);
	glm::mat4 model = glm::mat4(1.0f);// glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniform_loc.model, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(uniform_loc.view,  1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(uniform_loc.proj,  1, GL_FALSE, &proj[0][0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glUseProgram(0);
}


void Plane::Shutdown()
{
	glDeleteProgram(program);
}

void Plane::init_buffer()
{
	m_Polygon.CreatePlane(1.0f, 1.0f, m_PlaneMeshData);

	auto VertexSize = sizeof(ogl::Vertex) * m_PlaneMeshData.VertexData.size();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, &m_PlaneMeshData.VertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto Indexsize = sizeof(GLuint) * m_PlaneMeshData.IndexData.size();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indexsize, &m_PlaneMeshData.IndexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Plane::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ogl::Vertex), 0);
	glEnableVertexAttribArray(1);						  
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ogl::Vertex), (GLvoid*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);						 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ogl::Vertex), (GLvoid*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ogl::Vertex), (GLvoid*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Plane::init_shader()
{
	PlaneShader.init();
	PlaneShader.attach(GL_VERTEX_SHADER, "Plane.vert");
	PlaneShader.attach(GL_FRAGMENT_SHADER, "Plane.frag");
	PlaneShader.link();
	PlaneShader.info();
	program = PlaneShader.GetProgram();

	uniform_loc.model = glGetUniformLocation(program, "model");
	uniform_loc.view = glGetUniformLocation(program, "view");
	uniform_loc.proj = glGetUniformLocation(program, "proj");
	uniform_loc.colorTex = glGetUniformLocation(program, "colorTex");
	uniform_loc.normalTex = glGetUniformLocation(program, "normalTex");
}

void Plane::init_texture()
{
	colorTex = m_TextureMgr.LoadTexture("rock_color.tga");
	normalTex = m_TextureMgr.LoadTexture("rock_normal.tga");
}
}