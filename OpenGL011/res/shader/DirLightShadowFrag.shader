#version 330 core

// 材质
struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	
	sampler2D texture_specular1;
	float shininess;
};

// 定向光源
struct DirLight
{
	vec3 ambient;			// 环境光
	vec3 diffuse;			// 漫反射
	vec3 specular;			// 镜面反射

	vec3 direction;			// 光照方向
};

uniform Material u_material;
uniform DirLight u_dirLight;

uniform vec3 u_cameraPos;

uniform int u_texID;

uniform sampler2D u_depthMap;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;
in vec4 LightSpacePos;
out vec4 FragColor;

vec3 DirLightDiffuse();
vec3 DirLightSpecular(vec3 viewDir);
vec3 DirLightAmbient();
float InShadow();


void main()
{
	vec3 viewDir = normalize(u_cameraPos - FragPos);
	vec3 specular = DirLightSpecular(viewDir);
	vec3 diffuse = DirLightDiffuse();
	vec3 ambient = DirLightAmbient();
	vec4 texColor[2];
	float shadow = InShadow();
	texColor[0] = texture(u_material.texture_diffuse1, TexCoord);
	texColor[1] = texture(u_material.texture_diffuse2, TexCoord);
	specular = specular * (1.0f - shadow);
	diffuse = diffuse * (1.0f - shadow);
	FragColor = vec4((ambient + diffuse), 1.0f) * texColor[u_texID] + vec4(specular, 1.0f);
}

float InShadow()
{
	vec3 texCoord = LightSpacePos.xyz / LightSpacePos.w;	// -1<= xyz <= 1
	texCoord = texCoord * 0.5f + 0.5f;						// 0 <= xyz <= 1
	float closeDepth = texture(u_depthMap, texCoord.xy).r;
	float currentDepth = texCoord.z;
	float shadow;
	if(currentDepth > 1.0f)
		shadow = 0.0f;
	else
	{
		float bias = 0.01f;
		shadow = currentDepth-bias > closeDepth ? 1.0f : 0.0f;
	}
	return shadow;
}

vec3 DirLightDiffuse()
{
	vec3 lightDir = normalize(u_dirLight.direction);
	float strength = max(dot(Normal, -lightDir), 0.0f);
	vec3 diffuse = strength * u_dirLight.diffuse;
	return diffuse;
}

vec3 DirLightSpecular(vec3 viewDir)
{
	vec3 lightDir = normalize(u_dirLight.direction);
	float strength = max(dot(reflect(lightDir, Normal), viewDir), 0.0f);
	strength = pow(strength, u_material.shininess);
	vec3 specular = u_dirLight.specular * strength;
	return specular;
}

vec3 DirLightAmbient()
{
	return u_dirLight.ambient;
}