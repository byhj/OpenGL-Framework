#version 430 core

layout (location = 0) out vec4 g_FragColor;

in VS_OUT
{
  vec3 Normal;
  vec2 TexCoord;
  vec3 Tangent;
  vec3 Bitangent;
  vec3 Pos;
}vs_out;

uniform vec3 viewPos = vec3(0.0f, 0.0f, 10.0f);
uniform vec3 lightPos = vec3(1.0f, 0.0f, 1.0f);

uniform sampler2D colorTex;
uniform sampler2D normalTex;

void main(void)
{
   vs_out.Normal = normalize(vs_out.Normal);
   vs_out.Tangent = normalize(vs_out.Tangent);
   vs_out.Bitangent = normalize(vs_out.Bitangent);
   mat3 TBN = mat3(vs_out.Tangent, vs_out.Bitangent, vs_out.Normal);

   vec3 texColor = texture2D(colorTex, vs_out.TexCoord).rgb;
   vec3 normal = texture2D(normalTex, vs_out.TexCoord).rgb;

   //map [0, 1] to [-1, 1]
   normal = normal * 2.0f  - 1.0f;
   normal = TBN * normal;

   vec3 lightDir = lightPos - vs_out.Pos;
   float diff = max(dot(normal, lightDir), 0.0f);
   vec3 diffuse = diff * texColor;

   vec3 viewDir = viewPos - vs_out.Pos;
   vec3 reflectDir = reflect(-lightDir, normal);
   vec3 halfDir = normalize(reflectDir + viewDir);
   float spec = pow(max(dot(halfDir, normal), 0.0f), 32.0f);
   vec3 specular = spec * texColor;

   vec4 pixelColor = normalize(vec4(diffuse + specular, 1.0f));
   g_FragColor = pixelColor;
}