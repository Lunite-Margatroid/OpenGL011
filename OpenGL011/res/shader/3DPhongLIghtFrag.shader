// 只有一个点光源 采用phong模型
#version 330 core

struct Material
{
	// 漫反射贴图
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	// 镜面反射贴图
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	// 光泽度
	float shininess;
};

// 点光源结构
struct PointLight
{
	vec3 ambient;	// 环境光贡献
	vec3 diffuse;	// 漫反射光
	vec3 specular;	// 镜面反射

	vec3 position;	// 光源位置

	float kConstant;	// 光照衰减 常数项
	float kLinear;		// 光照衰减 一次项
	float kQuadratic;	// 光照衰减 二次项
};



in vec3 Normal;		// 法向量
in vec3 FragPos;	// 片段位置
in vec2 TexCoord;	// 纹理坐标

out vec4 FragColor;	// 输入color

uniform Material u_material;		// 模型材质
uniform vec3 u_cameraPos;			// 摄像机位置
uniform PointLight u_pointLight;	// 点光源结构


vec3 PointLightDiffuse(vec3 lightDir);
vec3 PointLightSpecular(vec3 lightDir, vec3 viewDir);
vec4 PointLightCtb(vec3 lightDir, vec3 viewDir, vec4 texColor);

void main()
{
	vec3 lightDir = normalize(FragPos - u_pointLight.position);
	vec3 viewDir = normalize(u_cameraPos - FragPos);
	vec4 texColor = texture(u_material.texture_diffuse1, TexCoord);
	FragColor = PointLightCtb(lightDir, viewDir, texColor);
}

vec4 PointLightCtb(vec3 lightDir, vec3 viewDir, vec4 texColor)
{
	float dist = distance(FragPos, u_pointLight.position);
	float attenuation = 1.0f/
		(u_pointLight.kConstant + u_pointLight.kLinear * dist + u_pointLight.kQuadratic * dist * dist);
	vec4 output = 
		texColor * vec4(u_pointLight.ambient + PointLightDiffuse(lightDir) , 1.0f)
		 + vec4(PointLightSpecular(lightDir, viewDir), 0.0f);
	output = output * attenuation;
	return output;
}

vec3 PointLightDiffuse(vec3 lightDir)
{
	vec3 diffuse;
	float strength = max(dot(-lightDir, Normal), 0.0f);
	diffuse = strength * u_pointLight.diffuse;
	return diffuse;
}

vec3 PointLightSpecular(vec3 lightDir, vec3 viewDir)
{
	float strength = max(dot(reflect(lightDir, Normal), viewDir), 0.0f);
	strength = pow(strength, u_material.shininess);
	vec3 specular = u_pointLight.specular * strength;
	return specular;
}