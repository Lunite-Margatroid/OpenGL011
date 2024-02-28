#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Camera_K.h"
#include "DirLight.h"
#include "DepthBuffer.h"
#include "Mesh3D.h"
namespace test
{
	class TestMesh3D :public Test
	{
	private:
		LM::VertexArray m_vao[2];
		LM::ElementBuffer m_ebo[2];
		LM::VertexBuffer m_vbo[2];

		LM::Shader m_shader;
		LM::Shader m_shaderShadowTex;
		LM::Shader m_shaderShadowed;
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

		LM::Shader* m_shaderDraw;

		LM::DepthBuffer m_depthMap;

		bool m_shadow;

		LM::Mesh3D m_meshCube;
		LM::Mesh3D m_meshFloor;
	public:
		TestMesh3D();
		~TestMesh3D();

		void OnRender() override;
		void OnUpdate(float deltaTime) override;
		void OnRenderImgui() override;

	};
}