#pragma once
#include "Test.h"
#include "Camera_K.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
namespace test
{
	class Test3D:public Test
	{
	private:
		LM::Shader m_shader;
		LM::Texture m_texture;
		LM::VertexBuffer m_vbo;
		LM::ElementBuffer m_ebo;
		LM::VertexArray m_vao;

	public:
		Test3D();
		~Test3D() {};

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnRenderImgui() override;
	};
}