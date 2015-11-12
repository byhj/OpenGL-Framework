#ifndef ShadowGUI_H
#define ShadowGUI_H

#include "ogl/Gui.h"

namespace byhj
{
	class ShadowGUI : public ogl::GUI
	{
	public:
		ShadowGUI() = default;
		~ShadowGUI() = default;

		void v_Init(int sw, int sh) override;
		void v_Render() override;
		void v_Shutdown() override;

	};
}
#endif