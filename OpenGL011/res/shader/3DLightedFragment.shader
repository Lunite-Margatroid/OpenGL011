// 3d有光源 blinn-phong测试用 
#version 330 core
// 多光源
// 材质struct
struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;

	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	float shininess;
};

// 光照
// 定向光
struct DirLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

// 点光源
struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;

	float kConstant;		// 常数项
	float kLinear;			// 一次项
	float kQuadratic;		// 2次项
};


// 聚光
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;

	// 渐变边界
	float innerbdr;
	float outerbdr;

	// 衰减
	float kConstant;		// 常数项
	float kLinear;			// 一次项
	float kQuadratic;		// 2次项
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform Material material;
uniform vec3 cameraPos;

uniform PointLight pointLight1;
// 是否blinn phong光照模型
uniform int u_blinn;

vec3 CalcPointLightDiffuse(PointLight pointLight, vec3 lightDir);
vec3 CalcPointLightSpecular(PointLight pointLight, vec3 lightDir, vec3 viewDir);
vec3 CalcPointLight(PointLight pointLight,vec3 viewDir, vec3 texDiffuseColor,vec3 texSpecularColor);
void main()
{
	vec3 viewDir = normalize(FragPos - cameraPos);
	vec4 texDiffuseColor = texture(material.texture_diffuse1, TexCoord);
	vec4 texSpecularColor = vec4(1.0f,1.0f,1.0f,1.0f);
	vec3 outputColor = CalcPointLight(pointLight1, viewDir, vec3(texDiffuseColor), vec3(texSpecularColor));
	FragColor = vec4(outputColor, 1.0f);
}

vec3 CalcPointLightDiffuse(PointLight pointLight,vec3 lightDir)
{
	vec3 diffuse;
	float strength = max(dot(lightDir, Normal), 0.0f);
	diffuse = strength * pointLight.diffuse;
	return diffuse;
}

vec3 CalcPointLightSpecular(PointLight pointLight, vec3 lightDir, vec3 viewDir)
{
	vec3 specular;
	float strength;
	if (u_blinn == 1)
	{
		// Blinn-Phong
		vec3 temp = normalize(lightDir - viewDir);
		strength = max(dot(temp, Normal), 0.0f);
		strength = pow(strength, material.shininess);
	}
	else
	{	// 冯氏光照模型
		vec3 reflectDir = reflect(lightDir, Normal);
		strength = max(dot(reflectDir, viewDir), 0.0f);
		strength = pow(strength, material.shininess);
	}
	specular = pointLight.specular * strength;
	return specular;
}

vec3 CalcPointLight(PointLight pointLight,vec3 viewDir, vec3 texDiffuseColor, vec3 texSpecularColor)
{
	vec3 lightDir = normalize(pointLight.position - FragPos);
	float dist = distance(pointLight.position, FragPos);
	float attenuation = 1.0f /
		(pointLight.kConstant + dist * pointLight.kLinear + dist * dist * pointLight.kQuadratic);
	vec3 lightColor = (pointLight.ambient + CalcPointLightDiffuse(pointLight, lightDir)) * texDiffuseColor
		+ CalcPointLightSpecular(pointLight, lightDir, viewDir) * texSpecularColor;
	return lightColor * attenuation;
}