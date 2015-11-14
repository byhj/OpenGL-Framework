#include "Shadow.h"

namespace byhj
{
	void Shadow::Init(int sw, int sh)
	{
		m_Aspect = static_cast<GLfloat>(sw) / sh;

		m_Model.LoadModel("armadillo.obj");
		m_Plane.LoadModel("plane.obj");

		init_shader();
		init_fbo(sw, sh);
	}

	void Shadow::Update()
	{

	}

	void Shadow::Render()
	{
		GLfloat time = glfwGetTime();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.2f, 5.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 proj  = glm::perspective(45.0f, m_Aspect, 0.1f, 1000.0f);


		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		GLfloat near_plane = 1.0f, far_plane = 7.5f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

		glm::vec3 lightPos(0.0f, 0.0f, 1.0f);
		glm::vec3 camPos = glm::vec3(0.0f, 1.0f, 4.0f);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(1.0));
		lightSpaceMatrix = lightProjection * lightView;

		glUseProgram(shadow_prog);

		glUniformMatrix4fv(glGetUniformLocation(shadow_prog, "u_LightSpaceMat"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_DEPTH_BUFFER_BIT);

		render_scene(shadow_prog);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glUseProgram(0);

		//////////////////////////////////////////////////////////////////////////////////////
		glUseProgram(scene_prog);

		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_Model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_View"),  1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_Proj"),  1, GL_FALSE, &proj[0][0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "u_LightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "u_ViewPos"), 1, &camPos[0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_LightSpaceMat"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		// Enable/Disable shadows by pressing 'SPscene_progACE'
		glUniform1i(glGetUniformLocation(scene_prog, "u_EnableShadow"), shadowFlag);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glUniform1i(glGetUniformLocation(scene_prog, "u_ShadowMap"), 0);

		glEnable(GL_DEPTH_TEST);

		render_scene(scene_prog);
		glUseProgram(0);


		glUseProgram(scene_prog);

		model = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_Model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_View"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_Proj"), 1, GL_FALSE, &proj[0][0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "u_LightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "u_ViewPos"), 1, &camPos[0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "u_LightSpaceMat"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		// Enable/Disable shadows by pressing 'SPscene_progACE'
		glUniform1i(glGetUniformLocation(scene_prog, "u_EnableShadow"), shadowFlag);

		m_Plane.Draw(scene_prog);

		glUseProgram(0);

	}

	void Shadow::render_scene(GLuint program)
	{
		m_Model.Draw(program);
	}


	void Shadow::init_shader()
	{
	    SceneShader.init();
		SceneShader.attach(GL_VERTEX_SHADER,   "scene.vert");
		SceneShader.attach(GL_FRAGMENT_SHADER, "scene.frag");
		SceneShader.link();
		SceneShader.info();
		scene_prog = SceneShader.GetProgram();

		ShadowShader.init();
		ShadowShader.attach(GL_VERTEX_SHADER,   "shadow.vert");
		ShadowShader.attach(GL_FRAGMENT_SHADER, "shadow.frag");
		ShadowShader.link();
		ShadowShader.info();
		shadow_prog = ShadowShader.GetProgram();
	}

	void Shadow::init_fbo(int sw, int sh)
	{
		glGenTextures(1, &depth_tex);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, sw, sh, 0, GL_DEPTH_COMPONENT, GL_FLAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0);

		//we don't need draw the color buffer
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
}