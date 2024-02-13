// 3d 直接采用纹理的颜色 无光源
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 modelTrans;
uniform mat4 viewTrans;
uniform mat4 projectionTrans;
uniform mat3 normalMat;


void main()
{
	FragPos = vec3(modelTrans * vec4(aPos, 1.0));
	gl_Position = projectionTrans * viewTrans * vec4(FragPos, 1.0f);
	
	Normal = normalMat * aNormal;
	TexCoord = aTexCoord;
}