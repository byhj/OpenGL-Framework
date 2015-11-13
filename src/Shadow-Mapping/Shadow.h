#ifndef Shadow_H
#define Shadow_H

#include "ogl/Shader.h"
#include "ogl/Model.h"
#include <glfw/glfw3.h>

namespace byhj
{
	class Shadow
	{
	public:
		Shadow()  = default;
		~Shadow() = default;

		void Init(int sw, int sh);
		void Update();
		void Render();
		void Shutdown();

		void init_fbo(int sw, int sh);
		GLuint GetDepthMap() const
		{
			return depth_tex;
		}
	
	private:
		void init_shader();
		void render_scene(GLuint program);

		struct UniformLoc
		{
			GLuint model;
			GLuint view;
			GLuint proj;
		}uniform_loc;

		GLuint scene_prog, shadow_prog;
		GLuint fbo, depth_tex;
		GLboolean shadowFlag;
		GLfloat m_Aspect = 1.0f;

		ogl::Model m_Model;
		ogl::Model m_Plane;
		ogl::Shader SceneShader, ShadowShader;
		
	};
}
#endif
