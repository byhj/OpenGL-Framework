#include "Shadow.h"

namespace byhj
{
	void Shadow::Init()
	{

	}

	void Shadow::Update()
	{

	}

	void Shadow::Render()
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view  = glm::mat4(1.0f);
		glm::mat4 proj  = glm::mat4(1.0f);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		GLfloat near_plane = 1.0f, far_plane = 7.5f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

		glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
		glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 4.0f);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(1.0));
		lightSpaceMatrix = lightProjection * lightView;

		glUseProgram(shadow_prog);

		glUniformMatrix4fv(glGetUniformLocation(shadow_prog, "u_LightSpaceMat"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_DEPTH_BUFFER_BIT);

		RenderScene(shadow_prog);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glUseProgram(0);

		//////////////////////////////////////////////////////////////////////////////////////
		glUseProgram(scene_prog);

		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "proj"), 1, GL_FALSE, &proj[0][0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "lightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(scene_prog, "viewPos"), 1, &camPos[0]);
		glUniformMatrix4fv(glGetUniformLocation(scene_prog, "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		// Enable/Disable shadows by pressing 'SPscene_progACE'
		glUniform1i(glGetUniformLocation(scene_prog, "shadows"), shadowFlag);


		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glUniform1i(glGetUniformLocation(scene_prog, "shadowMap"), 1);

		RenderScene(scene_prog);

		glUseProgram(0);
	}

	void Shadow::Update()
	{

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