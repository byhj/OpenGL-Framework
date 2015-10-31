#include "gui.h"

namespace byhj
{
	namespace ogl
	{
		void Gui::Init(int sw, int sh)
		{
			// Initialize the GUI
			TwInit(TW_OPENGL_CORE, NULL);
			TwWindowSize(sw, sh);

			TwBar * EulerGUI = TwNewBar("Euler settings");
			TwBar * QuaternionGUI = TwNewBar("Quaternion settings");
			TwSetParam(EulerGUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
			TwSetParam(QuaternionGUI, NULL, "position", TW_PARAM_CSTRING, 1, "808 16");

		}

		void Gui::Render()
		{
			// Draw tweak bars
			TwDraw();
		}

		void Gui::Shutdown()
		{
			// Terminate AntTweakBar and GLFW
			TwTerminate();
		}
	}
}