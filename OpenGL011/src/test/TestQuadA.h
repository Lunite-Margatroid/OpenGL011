#pragma once
#include "Test.h"
#include "Quad.h"
#include "Shader.h"
#include "imgui/imgui.h"
namespace test
{
	class TestQuadA :public Test
	{
	private:
		LM::Texture m_texture;
		LM::Quad m_quad;
		LM::Shader m_shader;

		glm::vec3 m_position;

		glm::mat4 m_mvp;
	public:
		TestQuadA();
		~TestQuadA();

		void OnRender() override;
		void OnRenderImgui() override;
		void OnUpdate(float deltaTime) override;
	};
}