#include "pch.h"
#include "TestQuadA.h"

test::TestQuadA::TestQuadA()
	:m_texture("./res/img/img_1.jpg",0, GL_RGB, GL_RGB),
	m_quad(m_texture,true),
	m_shader("./res/shader/TexVertexShader.shader", "./res/shader/TexFragmentShader.shader"),
	m_position(0.0f)
{
	
}

test::TestQuadA::~TestQuadA()
{
}

void test::TestQuadA::OnRender()
{
	m_shader.Bind();
	m_shader.SetUniformMatrix4f("u_mvp", false, glm::value_ptr(m_mvp));
	m_quad.Draw();
}

void test::TestQuadA::OnRenderImgui()
{
	ImGui::SliderFloat3("position", &m_position[0], -4.0f, 4.0f);
}

void test::TestQuadA::OnUpdate(float deltaTime)
{
	static glm::mat4 modelTrans(1.0f);
	static glm::mat4 projectTrans = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);

	modelTrans = glm::translate(glm::mat4(1.0f), m_position);
	modelTrans = glm::scale(modelTrans, glm::vec3(9.0f, 9.0f, 9.0f));

	m_mvp = projectTrans * modelTrans;
}
