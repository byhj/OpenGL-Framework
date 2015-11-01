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