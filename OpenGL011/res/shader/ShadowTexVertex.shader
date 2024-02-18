// 渲染深度贴图
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_lightTrans;
uniform mat4 u_modelTrans;

void main()
{
	gl_Position = u_lightTrans * u_modelTrans * vec4(aPos, 1.0f);
}