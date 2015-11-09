#ifndef Font_H
#define Font_H

#include "ogl/Shader.h"
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

namespace byhj
{
	class Font
	{
	public:
		Font() = default;
		~Font() = default;
		
		void Init(int sw, int sh);
		void Render(std::string text, GLfloat px, GLfloat py, GLfloat scale = 1.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
		void Shutdown();

	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();

	private:
		struct Character
		{
			GLuint texID;
			glm::vec2 size;
			glm::ivec2 bearing;
			GLuint advance;
		};

		std::map<GLchar, Character> m_Characters;
		GLuint m_VAO, m_VBO;
		GLuint m_Program;
		ogl::Shader m_FontShader;
		GLfloat sw, sh;

	};
}

#endif
