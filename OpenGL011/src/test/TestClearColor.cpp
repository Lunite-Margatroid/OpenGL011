#include "pch.h"
#include "TestClearColor.h"

test::TestClearColor::TestClearColor()
	:m_color{0.0f, 0.0f, 0.0f, 1.0f}
{
}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::OnRender()
{
	GLCall(glClearColor(m_color[0], m_color[1], m_color[2], m_color[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::OnRenderImgui()
{
	ImGui::Begin("TestClearColor");
	ImGui::ColorEdit4("clear color", m_color);
	ImGui::End();
}
