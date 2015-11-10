#include "Geometry.h"

namespace byhj
{

Geometry::Geometry()
{

}

Geometry::~Geometry()
{

}

void Geometry::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

void Geometry::Render()
{
	//Use this shader and vao data to render
	glUseProgram(program);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, m_MeshData.IndexData.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glUseProgram(0);
}


void Geometry::Shutdown()
{
	glDeleteProgram(program);
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
	program = GeometryShader.GetProgram();
}

}