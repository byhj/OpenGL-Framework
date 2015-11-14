#include "RotationGUI.h"

namespace byhj
{

	void RotationGUI::v_Init(int sw, int sh)
	{
		TwInit(TW_OPENGL_CORE, NULL);
		TwWindowSize(sw, sh);
		TwBar *pBar = TwNewBar("RotationBar");
		TwDefine(" RotationBar label='RotationBar' position='800 16' alpha=0 help='Use this bar to edit the tess.' ");
		TwAddVarRW(pBar, "Quaternion", TW_TYPE_QUAT4F, &m_Orientation, "showval=true open=true ");

	}

	void RotationGUI::v_Render()
	{
		TwDraw();
	}

	void RotationGUI::v_Shutdown()
	{
		TwTerminate();
	}
}