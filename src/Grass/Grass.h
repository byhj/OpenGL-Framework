#ifndef Grass_H
#define Grass_H

#include "ogl/Shader.h"
#include "ogl/TextureMgr.h"
#include <glfw/glfw3.h>
#include <random>
#include <glm/glm.hpp>
#include <vector>


const int GRASS_NUM = 1000;

namespace byhj
{
	class Grass
	{
	public:
		Grass()  = default;
		~Grass() = default;

		void Init();
		void Update();
		void Render();
		void Shutdown();

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();
		void init_texture();

		struct GrassType
		{
		    glm::vec3 Pos;
			glm::vec3 Color;
		};

		struct InstanceType
		{
			glm::vec3 Color;
			glm::mat4 Model;
		};
		struct Wind
		{
			float Rotation;
			int Direction;
		};
		struct UniformLoc
		{
			GLuint tex;
			GLuint view;
			GLuint proj;
		}uniform_loc;

		std::vector<GrassType> m_GrassType;
		std::vector<InstanceType> m_InstanceType;

		ogl::Shader m_GrassShader;
		ogl::TextureMgr m_TextureMgr;

		Wind m_Wind;
		GLuint grass_tex;
		GLuint grass_prog;
		GLuint grass_vao, grass_vbo, grass_ibo;
		GLuint grass_instance;

	};
}
#endif