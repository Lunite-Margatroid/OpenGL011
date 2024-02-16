#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_modelTrans;
uniform mat4 u_viewTrans;
uniform mat4 u_projectionTrans;
uniform mat3 u_normalMat;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{
	Normal = u_normalMat * aNormal;
	FragPos = vec3(u_modelTrans * vec4(aPos, 1.0f));
	gl_Position = u_projectionTrans * u_viewTrans * vec4(FragPos,1.0f);
	TexCoord = aTexCoord;
}