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

	private:
		ogl::Shader ShadowShader;
		
	};
}
#endif
