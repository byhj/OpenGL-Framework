#include "Geometry.h"

namespace byhj
{

Geometry::Geometry()
{

}

Geometry::~Geometry()
{

}

void Geometry::Init(int sw, int sh)
{
	m_Aspect = static_cast<GLfloat>(sw) / sh;

	init_buffer();
	init_vertexArray();
	init_shader();
}

void Geometry::Update()
{
  glUseProgram(m_Program);

  GLfloat time = glfwGetTime();
  glm::mat4 model = glm::rotate(glm::mat4(1.0f), time , glm::vec3(0.0f, 1.0f, 0.0f) );
  glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) );
  glm::mat4 proj = glm::perspective(45.0f, m_Aspect, 0.1f, 1000.0f);

  glUniformMatrix4fv(uniform_loc.model, 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(uniform_loc.view,  1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(uniform_loc.proj,  1, GL_FALSE, &proj[0][0]);
   
  glUseProgram(0);
}

void Geometry::Render()
{
	//Use this shader and vao data to render
	glUseProgram(m_Program);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, m_MeshData.IndexData.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glUseProgram(0);
}


void Geometry::Shutdown()
{
	glDeleteProgram(m_Program);
}

void Geometry::init_buffer()
{
	m_Polygon.CreateCube(1.0f, 1.0f, 1.0f, m_MeshData);

	auto VertexDataSize = sizeof(byhj::Vertex) * m_MeshData.VertexData.size();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexDataSize, &m_MeshData.VertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto IndexDataSize = sizeof(GLuint) * m_MeshData.IndexData.size();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexDataSize, &m_MeshData.IndexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Geometry::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), (GLvoid*)(sizeof(glm::vec3)) );
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), (GLvoid*)(2 *sizeof(glm::vec3)) );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Geometry::init_shader()
{
	GeometryShader.init();
	GeometryShader.attach(GL_VERTEX_SHADER, "Geometry.vert");
	GeometryShader.attach(GL_FRAGMENT_SHADER, "Geometry.frag");
	GeometryShader.link();
	GeometryShader.info();
	m_Program = GeometryShader.GetProgram();

	uniform_loc.model = glGetUniformLocation(m_Program, "u_Model");
	uniform_loc.view  = glGetUniformLocation(m_Program, "u_View");
	uniform_loc.proj  = glGetUniformLocation(m_Program, "u_Proj");


}

}