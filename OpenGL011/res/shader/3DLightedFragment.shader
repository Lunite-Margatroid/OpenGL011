// 3d�й�Դ blinn-phong������ 
#version 330 core
// ���Դ
// ����struct
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

// ����
// �����
struct DirLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

// ���Դ
struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;

	float kConstant;		// ������
	float kLinear;			// һ����
	float kQuadratic;		// 2����
};


// �۹�
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;

	// ����߽�
	float innerbdr;
	float outerbdr;

	// ˥��
	float kConstant;		// ������
	float kLinear;			// һ����
	float kQuadratic;		// 2����
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform Material material;
uniform vec3 cameraPos;

uniform PointLight pointLight1;
// �Ƿ�blinn phong����ģ��
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
	{	// ���Ϲ���ģ��
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