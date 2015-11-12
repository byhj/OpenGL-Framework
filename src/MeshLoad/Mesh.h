#ifndef MESH_H
#define MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace byhj
{

struct Vertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh {

public:

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
	{
		m_VertexData = vertices;
		m_IndexData  = indices;
		m_Textures   = textures;

		// Now that we have all the required data, set the vertex buffers and its attribute pointers.
		this->setupMesh();
	}

	// Render the mesh
	void Draw(GLuint program);

private:

	GLuint m_VAO, m_VBO, m_IBO;
	std::vector<Vertex>  m_VertexData;
	std::vector<GLuint>  m_IndexData;
	std::vector<Texture> m_Textures;

	// Initializes all the buffer objects/arrays
	void setupMesh();

};

}

#endif