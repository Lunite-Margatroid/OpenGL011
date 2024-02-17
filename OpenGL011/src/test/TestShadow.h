#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Camera_K.h"
#include "DirLight.h"

namespace test
{
	class TestShadow :public Test
	{
	private:
		LM::VertexArray m_vao;
		LM::ElementBuffer m_ebo;
		LM::VertexBuffer m_vbo;

		LM::Shader m_shader;
		LM::Texture m_texFloor;
		LM::Texture m_texCube;


		LM::DirLight m_dirLight;

		glm::vec3 m_lightDirection;
		glm::vec3 m_ambient;
		glm::vec3 m_specular;
		glm::vec3 m_diffuse;

		glm::vec3 m_cubePosition[2];
		glm::vec4 m_cubeRotation[2];

		float m_floorShininess;
		float m_cubeShininess;
	public:
		TestShadow();
		~TestShadow();

		void OnRender() override;
		void OnUpdate(float deltaTime) override;
		void OnRenderImgui() override;

	};
}