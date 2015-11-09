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

		bool GetGamma()
		{
			return m_Gamma;
		}
	private:
		
		glm::vec3 m_LightColors[4] =
		{
			glm::vec3(0.25),
			glm::vec3(0.50),
			glm::vec3(0.75),
			glm::vec3(1.00)
		};

		GLboolean m_Gamma;

	};
}
#endif