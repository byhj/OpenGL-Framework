#include "ogl/Gui.h"

#include <glm/glm.hpp>

namespace byhj
{

	class TriangleGui : public ogl::GUI
	{

	  public:
		   void Init(int sw, int sh)   override;
		   void Render()			   override;
		   void Shutdown()  		   override;

		   glm::vec4  GetColor() const
		   {
			   return bgColor;
		   }
		   bool GetRenderMode() const
		   {
			   return wire;
		   }
	 private:
		double time = 0, dt;// Current time and enlapsed time
		double turn = 0;    // Model turn counter
		double speed = 0.3; // Model rotation speed
		int wire = 0;       // Draw model in wireframe?
		glm::vec4 bgColor = glm::vec4(0.1f, 0.2f, 0.4f, 1.0f);         // Background color 
		unsigned char cubeColor[4] ={ 255, 0, 0, 128 }; // Model color (32bits RGBA)
	};

};