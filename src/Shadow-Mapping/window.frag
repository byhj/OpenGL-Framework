#version 430 core

layout (location = 0) out vec4 g_FragColor;

in VS_OUT
{
  vec2 TexCoord;
}vs_out;

uniform sampler2D shadowTex;

void main(void)
{
   vec4 texColor = texture2D(shadowTex, vs_out.TexCoord);

   g_FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
}