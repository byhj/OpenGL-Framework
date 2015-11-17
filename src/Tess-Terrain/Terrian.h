#ifndef Terrian_H
#define Terrian_H

#include "ogl/Shader.h"

namespace byhj
{
	class Terrian
	{
	public:
		void Init();
		void Update();
		void Render();
		void Shutdown();

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();


	};
}
#endif