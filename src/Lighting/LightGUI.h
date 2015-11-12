#ifndef LightGUI_H
#define LightGUI_H

#include <gl/glew.h>
#include "ogl/gui.h"
#include <glm/glm.hpp>

namespace byhj
{	
	// This example displays one of the following shapes
	typedef enum { LIGHT_PHONG = 0, LIGHT_BLINNE } LightModel;

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

		LightModel GetLightModel()
		{
			return m_LightModel;
		}
		glm::vec3 GetLight1()
		{
			return m_LightColors[0];
		}
		glm::vec3 GetLight2()
		{
			return m_LightColors[1];
		}
		glm::vec3 GetLight3()
		{
			return m_LightColors[2];
		}	
		glm::vec3 GetLight4()
		{
			return m_LightColors[3];
		}
	private:
		
		glm::vec3 m_LightColors[4] =
		{
			glm::vec3(0.5f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.5f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.0f)
		};

		GLboolean m_Gamma;
		LightModel m_LightModel = LIGHT_PHONG;
	};
}
#endif