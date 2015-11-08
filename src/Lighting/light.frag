#version 430 core

layout (location = 0) out vec3 g_FragColor;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
}vs_out;

uniform sampler2D woodTex;

uniform vec3 vLightPos[4];
uniform vec3 vLightColor[4];
uniform vec3 viewPos;

void main()
{
  vec3
}
