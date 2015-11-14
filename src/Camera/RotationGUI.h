#ifndef RotationGUI_H
#define RotationGUI_H

#include "ogl/gui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

namespace byhj
{

class RotationGUI : public ogl::GUI
{
public:
	 RotationGUI() = default;
	 ~RotationGUI() = default;
    
	 void v_Init(int sw, int sh) override; 
	 void v_Render() override;
	 void v_Shutdown() override;

	 glm::mat4 GetRotationMat()
	 {
		 return glm::mat4_cast(m_Orientation);
	 }
private:
	glm::quat m_Orientation;
};

}
#endif