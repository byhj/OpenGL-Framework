#version 430 core

layout (location = 0) in vec3 g_Position;
layout (location = 1) in vec3 g_Normal;
layout (location = 2) in vec2 g_TexCoord;

layout (location = 3) in vec3 gi_Color;
layout (location = 4) in mat4 gi_Model;

uniform mat4 u_View;
uniform mat4 u_Proj;

out VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
  vec3 Color;
}vs_out;

void main(void)
{
   mat4 mvp = u_Proj * u_View * gi_Model;

   vs_out.Color    = gi_Color;
   vs_out.TexCoord = g_TexCoord;
   vs_out.Normal   = g_Normal;
   vs_out.FragPos  = mat3(gi_Model) * g_Position;

   gl_Position =  gi_Model * vec4(g_Position , 1.0f);
}