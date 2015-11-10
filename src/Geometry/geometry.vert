#version 430 core

layout (location = 0) in vec3 g_Position;
layout (location = 1) in vec3 g_Normal;
layout (location = 2) in vec2 g_TexCoord;

void main(void)
{
   gl_Position = vec4(g_Position, 1.0f);
}