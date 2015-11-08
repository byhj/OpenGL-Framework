#ifndef LightGUI_H
#define LightGUI_H

#include <gl/glew.h>
#include "ogl/gui.h"
#include <glm/glm.hpp>

namespace byhj
{
	class LightGUI : public ogl::GUI
	{
	public:
		LightGUI() = default;
		~LightGUI() = default;

		void v_Init(int sw, int sh) override;
		void v_Render() override;
		void v_Shutdown();

	private:
		
		glm::vec3 m_LightColors[4];
		GLboolean m_Gamma;

	};
}
#endif