#include "TriangleGui.h"

namespace byhj
{
	void TriangleGui::Init(int sw, int sh)
	{
		ogl::GUI::Init(sw, sh);
		TwBar *bar = TwNewBar("TweakBar");
		TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.
																										   // Add 'speed' to 'bar': it is a modifable (RW) variable of type TW_TYPE_DOUBLE. Its key shortcuts are [s] and [S].
		TwAddVarRW(bar, "speed", TW_TYPE_DOUBLE, &speed,
			" label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");

		// Add 'wire' to 'bar': it is a modifable variable of type TW_TYPE_BOOL32 (32 bits boolean). Its key shortcut is [w].
		TwAddVarRW(bar, "wire", TW_TYPE_BOOL32, &wire,
			" label='Wireframe mode' key=w help='Toggle wireframe display mode.' ");

		// Add 'time' to 'bar': it is a read-only (RO) variable of type TW_TYPE_DOUBLE, with 1 precision digit
		TwAddVarRO(bar, "time", TW_TYPE_DOUBLE, &time, " label='Time' precision=1 help='Time (in seconds).' ");

		// Add 'bgColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR3F (3 floats color)
		TwAddVarRW(bar, "bgColor", TW_TYPE_COLOR3F, &bgColor[0], " label='Background color' ");

		// Add 'cubeColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR32 (32 bits color) with alpha
		TwAddVarRW(bar, "Triangle Color", TW_TYPE_COLOR32, &cubeColor,
			" label='Triangle color' alpha help='Color and transparency of the Triangle.' ");
	}

	void TriangleGui::Render()
	{
		ogl::GUI::Render();
	}

	void TriangleGui::Shutdown()
	{
		ogl::GUI::Shutdown();
	}
}
