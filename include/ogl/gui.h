#ifndef __Gui_H_
#define __Gui_H_

#include "AntTweakBar.h"

namespace byhj
{
	namespace ogl
	{
		class GUI
		{
		public:
			 GUI();
			virtual ~GUI();

			virtual void v_Init(int sw, int sh) = 0;
			virtual void v_Render() = 0;
			virtual void v_Shutdown() = 0;
		private:

		};
	}
}


#endif // __Gui_H_
