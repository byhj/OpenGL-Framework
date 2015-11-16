#include "Grass.h"
#include <math.h>

namespace byhj
{

const static GLfloat VertexData[] = 
{
	0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f

};

const static GLuint IndexData[] = 
{
	0, 1, 2,
	2, 3, 0
};

	void Grass::Init()
	{
		init_buffer();
		init_vertexArray();
		init_shader();
		init_texture();
	}

	void Grass::Update()
	{
		if (m_Wind.Direction == 1)
		{
			m_Wind.Rotation += 0.1f;
			if (m_Wind.Rotation > 10.0f)
			{
				m_Wind.Direction = 2;
			}
		}
		else
		{
			m_Wind.Rotation -= 0.1f;
			if (m_Wind.Rotation < -10.0f)
			{
				m_Wind.Direction = 1;
			}
		}
		
		glm::vec3 modelPos;
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

		// Load the instance buffer with the updated locations.
		for (int i = 0; i < GRASS_NUM; i++)
		{
			// Get the position of this piece of foliage.
			modelPos.x = m_GrassType[i].Pos.x;
			modelPos.y = -0.1f;
			modelPos.z = m_GrassType[i].Pos.z;

			// Calculate the rotation that needs to be applied to the billboard model to face the current camera position using the arc tangent function.
			float angle = atan2(modelPos.x - cameraPos.x, modelPos.z - cameraPos.z) * (180.0f / glm::pi<float>());

			// Convert rotation into radians.
			float rotation = (float)angle * 0.0174532925f;

			// Setup the X rotation of the billboard.
			glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 1.0f, 0.0f));

			// Get the wind rotation for the foliage.
			float windRotation = m_Wind.Rotation * 0.0174532925f;

			// Setup the wind rotation.
			glm::mat4 rotateMatrix2 = glm::rotate(glm::mat4(1.0f), windRotation, glm::vec3(1.0f, 0.0f, 0.0f)); 

			// Setup the translation matrix.
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), modelPos);

			// Create the final matrix and store it in the instances array.
			glm::mat4 finalMatrix = rotateMatrix * rotateMatrix2;
			m_InstanceType[i].Model = finalMatrix * translationMatrix;
		}

		glBindVertexArray(grass_vao);

		glBindBuffer(GL_ARRAY_BUFFER, grass_instance);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceType) * GRASS_NUM, &m_InstanceType[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void Grass::Render()
	{
		glUseProgram(grass_prog);
		glBindVertexArray(grass_vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, grass_tex);
		glUniform1i(uniform_loc.tex, 0);

		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 proj = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);
		glUniformMatrix4fv(uniform_loc.view, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(uniform_loc.proj, 1, GL_FALSE, &proj[0][0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, GRASS_NUM);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Grass::Shutdown()
	{
		glDeleteProgram(grass_prog);
		glDeleteVertexArrays(1, &grass_vao);
		glDeleteBuffers(1, &grass_vbo);
		glDeleteBuffers(1, &grass_ibo);
	}

	void Grass::init_buffer()
	{
		m_Wind.Rotation = 0.0f;
	    m_Wind.Direction = 1;
		m_GrassType.resize(GRASS_NUM);
		m_InstanceType.resize(GRASS_NUM);

		glGenBuffers(1, &grass_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, grass_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &grass_instance);
		glBindBuffer(GL_ARRAY_BUFFER, grass_instance);
		glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceType) * GRASS_NUM, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &grass_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grass_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexData), IndexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		auto currTime = glfwGetTime();
		// Seed the random generator.
		srand( (int)currTime );
	

		// Set random positions and random colors for each piece of foliage.
		for (int i = 0; i < GRASS_NUM; i++)
		{
			m_GrassType[i].Pos.x = ((float)rand() / (float)(RAND_MAX)) * 9.0f - 4.5f;
			m_GrassType[i].Pos.y = 0.0f;
			m_GrassType[i].Pos.z = ((float)rand() / (float)(RAND_MAX)) * 9.0f - 4.5f;

			float red = ((float)rand() / (float)(RAND_MAX)) * 1.0f;
			float green = ((float)rand() / (float)(RAND_MAX)) * 1.0f;

			m_GrassType[i].Color.r = red + 1.0f;
			m_GrassType[i].Color.g = green + 0.5f;
			m_GrassType[i].Color.b = 0.0f;

			m_InstanceType[i].Color = m_GrassType[i].Color;
		}

	}

	void Grass::init_vertexArray()
	{
		glGenVertexArrays(1, &grass_vao);
		glBindVertexArray(grass_vao);

		glBindBuffer(GL_ARRAY_BUFFER, grass_vbo);
        glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec3)));

		glBindBuffer(GL_ARRAY_BUFFER, grass_instance);
		glVertexAttribDivisor(3, 1);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceType), 0);

		//Because mat is 4 * vec4, so we should use four attribArray
		for (int i = 0; i != 4; ++i)
		{
			glEnableVertexAttribArray(4 + i);
			glVertexAttribDivisor(4 + i, 1);
			glVertexAttribPointer(4 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceType), (GLvoid*)(sizeof(glm::vec4) * i + sizeof(glm::vec3))) ;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grass_ibo);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Grass::init_shader()
	{
		m_GrassShader.init();
		m_GrassShader.attach(GL_VERTEX_SHADER, "grass.vert");
		m_GrassShader.attach(GL_FRAGMENT_SHADER, "grass.frag");
		m_GrassShader.link();
		m_GrassShader.info();

		grass_prog = m_GrassShader.GetProgram();
		uniform_loc.tex = glGetUniformLocation(grass_prog, "u_GrassTex");
		uniform_loc.view = glGetUniformLocation(grass_prog, "u_View");
		uniform_loc.proj = glGetUniformLocation(grass_prog, "u_Proj");

	}

	void Grass::init_texture()
	{
		m_TextureMgr.Init();
		m_TextureMgr.LoadDDS("grass.dds");
		grass_tex = m_TextureMgr.GetTexID("grass.dds");
	}
}