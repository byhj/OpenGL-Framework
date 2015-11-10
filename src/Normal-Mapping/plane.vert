#version 430 core

layout (location = 0) in vec3 g_Position;
layout (location = 1) in vec3 g_Normal;
layout (location = 2) in vec2 g_TexCoord;
layout (location = 3) in vec3 g_Tangent;

out VS_OUT
{
  vec3 Normal;
  vec2 TexCoord;
  vec3 Tangent;
  vec3 Bitangent;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
   mat4 mvp = proj * view * model;
   gl_Position = mvp *  vec4(g_Position, 1.0f);

   vs_out.Normal   = transpose(inverse(mat3(view * model))) * g_Normal;
   vs_out.TexCoord = g_TexCoord;
   vs_out.Tangent  = g_Tangent;
   vs_out.Bitangent = cross(g_Normal, g_Tangent);

}