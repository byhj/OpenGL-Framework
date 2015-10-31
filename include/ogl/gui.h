#ifndef __Gui_H_
#define __Gui_H_

#include "AntTweakBar.h"

namespace byhj
{
	namespace ogl
	{
		class Gui
		{
		public:
			Gui() = default;
			~Gui() = default;

			void Init(int sw, int sh);
			void Render();
			void Shutdown();
		};
	}
}


#endif // __Gui_H_
