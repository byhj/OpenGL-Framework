#ifndef TESSGUI_H
#define TESSGUI_H

#include <glm/glm.hpp>
#include <gl/glew.h>

#include "ogl/Gui.h"


namespace byhj
{

	class TessGUI : public ogl::GUI
	{
	public:
		TessGUI()  = default;
		~TessGUI() = default;

		void v_Init(int sw, int sh)  override;
		void v_Render() override;
		void v_Shutdown() override;

		bool GetWireFrame() const;
		GLuint GetTessInnder() const;
		GLuint GetTessOuter() const;

		glm::vec3 GetLightDir() const;
		glm::vec4 GetAmbientMat() const;
		glm::vec4 GetDiffuseMat() const;

	private:
		GLboolean m_WireFrame = false;
		GLuint m_TessInner = 2;
		GLuint m_TessOuter = 3;
		glm::vec4 m_AmbientMat = glm::vec4(0.04f, 0.04f, 0.04f, 1.0f);
		glm::vec4 m_DiffuseMat = glm::vec4(0.0f, 0.75, 0.75, 1.0f);
		glm::vec3 m_LightDir =   glm::vec3(-0.57f, -0.57f, -0.57f);
	};
}
#endif
