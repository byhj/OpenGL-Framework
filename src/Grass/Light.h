#ifndef Light_H
#define Light_H

#include <glm/glm.hpp>
#include <string>

namespace byhj
{
    class Light
    {
    public:
    	Light() = default;
    	~Light() = default;
    
    	void Init();
    	void Render();
    	void Shutdown();
    
    private:
    	bool m_Active;
    	glm::vec4 m_Pos;    //light position(in homogeneous coordinates, ie.Pos[4]=1)
    	glm::vec4 m_Color;
    	float   m_Radius;   // radius of the light influence area 
    	float m_Dis, m_Angle, m_Height, m_Speed;
    	std::string name;
    
    };
}
#endif