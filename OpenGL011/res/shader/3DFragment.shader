// 3d ֱ�Ӳ����������ɫ �޹�Դ
#version 330 core
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

in vec3 normal;				// ���Զ������Եķ�����
in vec3 fragPos;			// Ƭ������
in vec2 TexCoord;			// ��������

out vec4 FragColor;			// outputƬ����ɫ

uniform Material material;	// ����

void main()
{
	FragColor = texture(material.texture_diffuse1, TexCoord);
	//FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}