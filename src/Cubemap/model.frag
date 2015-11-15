#version 330

layout (location = 0) out vec4 g_FragColor;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
}vs_out;

uniform vec3 u_ViewPos = vec3(0.0f, 0.0f, 1.0f);
uniform samplerCube u_Cubemap;

void main()
{
    vec3 lightDir = u_ViewPos - vs_out.FragPos;
	vec3 reflectDir = reflect(-lightDir, vs_out.Normal);

    g_FragColor = texture(u_Cubemap, reflectDir);
}