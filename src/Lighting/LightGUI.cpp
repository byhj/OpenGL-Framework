#include "LightGUI.h"

namespace byhj
{

	void LightGUI::v_Init(int sw, int sh)
	{
		TwInit(TW_OPENGL_CORE, 0);
		TwWindowSize(sw, sh);

		TwBar *pBar = TwNewBar("LightBar");


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