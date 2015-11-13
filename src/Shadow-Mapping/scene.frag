#version 430 core

layout (location = 0) out vec4 g_FragColor;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
  vec4 LightSpacePos;
}vs_out;

uniform sampler2D u_ShadowMap;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform bool u_EnableShadow;

float CalcShadow(vec4 lightSpacePos);

void main(void)
{
   vec3 texColor = vec3(1.0f);//texture2D(u_ColorTex, vs_out.TexCoord);
   vec3 normal   = normalize(vs_out.Normal);
   vec3 lightColor = vec3(0.3f);
   
   //ambient
   vec3 ambient = vec3(0.3f);

   //diffuse
   vec3 lightDir = normalize(u_LightPos - vs_out.FragPos);
   float diff    = max(dot(lightDir, vs_out.Normal), 0.0f);
   vec3 diffuse  = diff * lightColor;
   
   //specular
    vec3 viewDir = normalize(u_ViewPos - vs_out.FragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec   = pow(max(dot(halfDir, vs_out.Normal), 0.0f), 32.0f);
	vec3 specular = spec * lightColor;

	float shadowVal = u_EnableShadow ? CalcShadow(vs_out.LightSpacePos) : 0.0f;

	vec3 lighting = (ambient + (1.0f - shadowVal) * (diffuse + specular) ) * texColor;

	g_FragColor = vec4(lighting, 1.0f);
}


float CalcShadow(vec4 lightSpacePos)
{
    vec3 projCoord = lightSpacePos.xyz / lightSpacePos.w;
	//map to [0, 1]
	projCoord = projCoord * 0.5 + 0.5f;

	float closestDepth = texture2D(u_ShadowMap, projCoord.xy).r;
	float currDepth = projCoord.z;

	//Add Bias to slove the shadow acon
	vec3 normal = normalize(vs_out.Normal);
	vec3 lightDir = normalize(u_LightPos - vs_out.FragPos);
	float bias = max(0.05 * (1.0f - dot(normal, lightDir)), 0.005);

	//PCF
	float shadowVal;
	vec2 texelSize = 1.0f / textureSize(u_ShadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
	   for (int y = -1; y <= 1; ++y)
	   {
	      float pcfDepth = texture2D(u_ShadowMap, projCoord.xy + vec2(x, y) * texelSize).r;
		  shadowVal += (currDepth - bias > pcfDepth ? 1.0f : 0.0f);
	   }
	}

	shadowVal /= 9.0f;

	    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoord.z > 1.0)
        shadowVal = 0.0;

	return shadowVal;
}