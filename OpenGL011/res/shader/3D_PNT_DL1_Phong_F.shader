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

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;
out vec4 FragColor;

vec3 DirLightDiffuse();
vec3 DirLightSpecular(vec3 viewDir);
vec3 DirLightAmbient();

void main()
{
	vec3 viewDir = normalize(u_cameraPos - FragPos);
	vec3 specular = DirLightSpecular(viewDir);
	vec3 diffuse = DirLightDiffuse();
	vec3 ambient = DirLightAmbient();
	vec4 texColor;
	texColor = texture(u_material.texture_diffuse1, TexCoord);
	FragColor = vec4((ambient + diffuse), 1.0f) * texColor + vec4(specular, 1.0f);
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