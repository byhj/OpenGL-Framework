#include "TessGUI.h"

namespace byhj
{
	void TessGUI::v_Init(int sw, int sh)
	{
		TwInit(TW_OPENGL_CORE, 0);
		TwWindowSize(sw, sh);

		TwBar *pBar = TwNewBar("TessGUI");
		TwDefine(" TessGUI label='TessGUI' position='750 16' alpha=0 help='Use this bar to edit the tess.' ");
		
		TwAddVarRW(pBar, "wire", TW_TYPE_BOOL32, &m_WireFrame,
				" label='Wireframe mode' key=w help='Toggle wireframe display mode.' ");

		TwAddVarRW(pBar, "LightDir", TW_TYPE_DIR3F, &m_LightDir, 
			       " label='Light direction' opened=true help='Change the light direction.' ");
		TwAddVarRW(pBar, "AmbientMat", TW_TYPE_COLOR3F, &m_AmbientMat, " group = 'Material' ");
		TwAddVarRW(pBar, "DiffuseMat", TW_TYPE_COLOR3F, &m_DiffuseMat, " group = 'Material' ");
		TwAddVarRW(pBar, "TessInner",  TW_TYPE_UINT32, &m_TessInner, " group = 'Tess' ");
		TwAddVarRW(pBar, "TessOuter", TW_TYPE_UINT32, &m_TessOuter, " group = 'Tess' ");
	}

	void TessGUI::v_Render()
	{
		TwDraw();
	}

	void TessGUI::v_Shutdown()
	{
		TwTerminate();
	}

	bool TessGUI::GetWireFrame() const
	{
		return m_WireFrame;
	}

	GLuint TessGUI::GetTessInnder()const
	{
		return m_TessInner;
	}
	GLuint TessGUI::GetTessOuter()const
	{
		return m_TessOuter;
	}
	glm::vec3 TessGUI::GetLightDir() const
	{
		return m_LightDir;
	}
	glm::vec4 TessGUI::GetAmbientMat()const
	{
		return m_AmbientMat;
	}
	glm::vec4 TessGUI::GetDiffuseMat()const
	{
		return m_DiffuseMat;
	}
}