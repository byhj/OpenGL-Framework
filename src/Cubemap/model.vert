#version 330

layout  (location = 0) in vec3 g_Position;
layout  (location = 1) in vec3 g_Normal;
layout  (location = 2) in vec2 g_TexCoord;

out VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
}vs_out;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{

    mat4 mvp  = u_Proj * u_View * u_Model;
	mat3 normal_mat = mat3(transpose(inverse(u_View * u_Model) ) );
	vs_out.Normal = normal_mat * g_Position;
	vs_out.FragPos = mat3(u_Model) * g_Position;
	vs_out.TexCoord = g_TexCoord;

    gl_Position = mvp * vec4( g_Position, 1.0f);
}

