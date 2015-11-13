#version 430 core

layout (location = 0) in vec3 g_Position;

uniform mat4 lightMat;

void main(void)
{
   gl_Position = lightMat * vec4(g_Position, 1.0f);
}