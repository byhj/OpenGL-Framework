#version 430 core

layout (location = 0) out vec4  FragColor;

in GE_OUT
{
  vec3 FacetNormal;
  vec3 TriDistance;
  vec3 PatchDistance;
}ge_out;

uniform vec3 lightDir = vec3(0.0f, 2.0f, 0.0f);
uniform vec4 diffuseMat;
uniform vec4 ambientMat;

float amplify(float d, float scale, float offset)
{
  d = scale * d + offset;
  d = clamp(d, 0, 1);
  d = 1 - exp2(-2 * d * d);
  
  return d;
}


void main(void)
{
  vec3 N = normalize(ge_out.FacetNormal);
  float df = abs(dot(N, lightDir));
  vec4 color = ambientMat + diffuseMat;

  float d1 = min(min(ge_out.TriDistance.x, ge_out.TriDistance.y), ge_out.TriDistance.z);
  float d2 = min(min(ge_out.PatchDistance.x, ge_out.PatchDistance.y), ge_out.PatchDistance.z);

   color = amplify(d1, 40, -0.5) * amplify(d2, 60, -0.5) * color;

   FragColor = color;
}