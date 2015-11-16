#version 430 core

layout (location = 0) out vec4 g_FragColor;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
  vec3 Color;
}vs_out;

uniform sampler2D u_GrassTex;

void main(void)
{
   vec4 texColor = texture2D(u_GrassTex, vs_out.TexCoord);
   texColor *= vec4(vs_out.Color, 1.0f);

   texColor = normalize(texColor);

   g_FragColor = texColor;
}