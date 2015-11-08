#ifndef LightGUI_H
#define LightGUI_H

#include "ogl/gui.h"

namespace byhj
{
	class LightGUI : public ogl::GUI
	{
	public:
		LightGUI() = default;
		~LightGUI() = default;

		void v_Init(int sw, int sh) override;
		void v_Render() override;
		void v_Shutdown();

	private:

	};
}
#endif