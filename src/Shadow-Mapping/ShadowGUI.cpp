#include "ShadowGUI.h"

namespace byhj
{
	void ShadowGUI::v_Init(int sw, int sh)
	{

	}

	void ShadowGUI::v_Render()
	{
		TwDraw();
	}

	void ShadowGUI::v_Shutdown()
	{
		TwTerminate();
	}
}