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

			virtual void Init(int sw, int sh);
			virtual void Render();
			virtual void Shutdown();
		};
	}
}


#endif // __Gui_H_
