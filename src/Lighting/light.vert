#version 430 core

layout (location = 0) in vec3 g_Position;
layout (location = 1) in vec3 g_Normal;
layout (location = 2) in vec2 g_TexCoord;

out VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
}vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
   mat4 mvp =  proj * view * model;
   mat3 normal_mat = mat3(view * model);

   gl_Position = mvp * vec4(g_Position, 1.0f);
   vs_out.FragPos = model * g_Position;
   vs_out.Normal = transpose(inverse(normal_mat * g_Normal));
   vs_out.TexCoor = g_TexCoord;

}
