#include "DebugWindow.h"

namespace byhj
{

static const GLfloat VertexData[] = 
{
	-0.8f, -0.8f, 0.0f,   0.0f, 0.0f,
	 0.8f, -0.8f, 0.0f,   1.0f, 0.0f,
	 0.8f,  0.8f, 0.0f,   1.0f, 1.0f,
	-0.8f,  0.8f, 0.0f,   0.0f, 1.0f
};

static const GLuint IndexData[] = 
{
	0, 1, 2,
	2, 3, 0
};
	void DebugWindow::Init(int depthWidth, int depthHeight)
	{
		glViewport(0, 0, depthWidth, depthHeight);

		init_buffer();
		init_vertexArray();
		init_shader();
	}
	
	void DebugWindow::Update()
	{

	}

	void DebugWindow::Render(GLuint texID)
	{
		glUseProgram(m_Program);
		glBindVertexArray(vao);

		//Map the shadow texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glUniform1i(shadowTex_loc, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
        glUseProgram(0);
	}

	void DebugWindow::Shutdown()
	{
	}

	void DebugWindow::init_buffer()
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexData), IndexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void DebugWindow::init_vertexArray()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,  (GLvoid*)(3 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void DebugWindow::init_shader()
	{
		m_DebugShader.init();
		m_DebugShader.attach(GL_VERTEX_SHADER, "window.vert");
		m_DebugShader.attach(GL_FRAGMENT_SHADER, "window.frag");
		m_DebugShader.link();
		m_DebugShader.info();

		m_Program = m_DebugShader.GetProgram();
		shadowTex_loc = glGetUniformLocation(m_Program, "shadowTex");


	}
}