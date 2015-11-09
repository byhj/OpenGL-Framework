#include "LightGUI.h"

namespace byhj
{

	void LightGUI::v_Init(int sw, int sh)
	{
		TwInit(TW_OPENGL_CORE, 0);
		TwWindowSize(sw, sh);

		TwBar *pBar = TwNewBar("LightBar");
		TwDefine(" LightBar label='LightBar' position='750 16' alpha=0 help='Use this bar to edit the tess.' ");

		TwAddVarRW(pBar, "Gamma", TW_TYPE_BOOL32, &m_Gamma, "");

		TwAddVarRW(pBar, "Light1", TW_TYPE_COLOR3F, &m_LightColors[0], " group = 'Light' ");
		TwAddVarRW(pBar, "Light2", TW_TYPE_COLOR3F, &m_LightColors[1], " group = 'Light' ");
		TwAddVarRW(pBar, "Light3", TW_TYPE_COLOR3F, &m_LightColors[2], " group = 'Light' ");
		TwAddVarRW(pBar, "Light4", TW_TYPE_COLOR3F, &m_LightColors[3], " group = 'Light' ");

		//TwEnumVal LightType[2] = { {phong, "Phong"}, 
		//TwAddVarRW(pBar, "LightModel", LightType, )
	}

	void LightGUI::v_Render()
	{
		TwDraw();
	}

	void LightGUI::v_Shutdown()
	{
		TwTerminate();
	}

}