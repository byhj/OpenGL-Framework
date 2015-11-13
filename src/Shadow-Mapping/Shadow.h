#ifndef Shadow_H
#define Shadow_H

#include "ogl/Shader.h"

namespace byhj
{
	class Shadow
	{
	public:
		Shadow()  = default;
		~Shadow() = default;

		void Init();
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
		GLuint scene_prog, shadow_prog;
		GLuint fbo, depth_tex;
		GLboolean shadowFlag;
		ogl::Shader SceneShader, ShadowShader;
		
	};
}
#endif
