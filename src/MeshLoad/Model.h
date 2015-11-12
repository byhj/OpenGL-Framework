#ifndef MODEL_H
#define MODEL_H

// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace byhj
{

GLint TextureFromFile(const char* path, std::string directory);

class Model
{
public:
	Model()	= default;
   ~Model() = default;

	// Draws the model, and thus all its meshes
	void Draw(GLuint program);
	void LoadModel(std::string path);

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:

	/*  Model Data  */
	std::vector<Mesh> m_Meshes;
	std::string m_Directory = "../../media/objects/";
	std::vector<Texture> m_Textures;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
};

}

#endif