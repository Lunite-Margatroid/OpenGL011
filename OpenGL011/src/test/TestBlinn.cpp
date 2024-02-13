#include "pch.h"
#include "TestBlinn.h"

extern LM::Camera_K& pCamera;

namespace test
{
	TestBlinn::TestBlinn()
		:m_shader("./res/shader/3DVertex.shader", "./res/shader/3DFragment.shader"),
		m_shaderPhong("./res/shader/3DVertex.shader", "./res/shader/3DPhongLightFrag.shader"),
		m_shaderBlinn("./res/shader/3DVertex.shader", "./res/shader/3DBlinnLightFrag.shader"),
		m_texture("./res/img/floor2.jpg", 0, GL_RGB, GL_RGB),
		m_blinn(true),
		m_shininess(16.0f)
	{
		float vertex[] =
		{
			//	位置坐标				法向量				纹理坐标
				-50.0f, -1.0f, -50.0f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
				-50.0f, -1.0f, 50.0f,	0.0f, 1.0f, 0.0f,	0.0f, 20.0f,
				50.0f, -1.0f, 50.0f,	0.0f, 1.0f, 0.0f,	20.0f, 20.0f,
				50.0f, -1.0f, -50.0f,	0.0f, 1.0f, 0.0f,	20.0f, 0.0f,
		};

		unsigned int index[] =
		{
			0,1,2,3
		};

		m_vbo.Init(sizeof(vertex), vertex);
		m_ebo.Init(4, index);
		m_vao.Bind();
		m_vao.PushAttrib<float>(3);
		m_vao.PushAttrib<float>(3);
		m_vao.PushAttrib<float>(2);
		m_vao.ApplyLayout();

		if (m_blinn)
			m_currentShader = &m_shaderBlinn;
		else
			m_currentShader = &m_shaderPhong;
	}
	TestBlinn::~TestBlinn()
	{
	}
	void TestBlinn::OnUpdate(float deltaTime)
	{
		static glm::mat4 modelTrans(1.0f);
		static glm::mat4 viewTrans(1.0f);
		static glm::mat4 projectionTrans(1.0f);
		static glm::mat3 normalTrans(1.0f);
		static glm::vec3 cameraPos;
		viewTrans = pCamera.GetViewTrans();
		projectionTrans = pCamera.GetProjectionTrans();
		normalTrans = glm::mat3(transpose(inverse(modelTrans)));
		cameraPos = pCamera.GetPosition();

		m_currentShader->Bind();
		m_currentShader->SetUniformModelTrans(modelTrans);
		m_currentShader->SetUniformViewTrans(viewTrans);
		m_currentShader->SetUniformProjectionTrans(projectionTrans);
		m_currentShader->SetUniformNormalMat(normalTrans);
		m_currentShader->SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
		m_currentShader->SetUniformTexture("u_material.texture_diffuse1", m_texture.GetIndex());
		m_pointLight.SetUniformLight("u_pointLight", *m_currentShader);
		m_currentShader->SetUniform1f("u_material.shininess", m_shininess);

		if (m_blinn)
			m_currentShader = &m_shaderBlinn;
		else
			m_currentShader = &m_shaderPhong;
	}
	void TestBlinn::OnRender()
	{
		
		m_currentShader->Bind();

		m_vao.Bind();
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
	}
	void TestBlinn::OnRenderImgui()
	{
		static glm::vec3 ambient;
		static glm::vec3 specular;
		static glm::vec3 diffuse;
		static glm::vec3 position;
		static float kAttenuation[3];
		ambient = m_pointLight.GetAmbient();
		specular = m_pointLight.GetSpecular();
		diffuse = m_pointLight.GetDiffuse();
		position = m_pointLight.GetLightPosition();
		kAttenuation[0] = m_pointLight.GetKConstant();
		kAttenuation[1] = m_pointLight.GetKLinear();
		kAttenuation[2] = m_pointLight.GetKQuadratic();

		ImGui::Checkbox("Blinn-Phong", &m_blinn);
		ImGui::Text("PointLight: ");
		ImGui::SliderFloat3("Ambient", &ambient[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular", &specular[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse", &diffuse[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Position", &position[0], -3.0f, 3.0f);
		ImGui::SliderFloat("Shininess", &m_shininess, 0.0f, 64.0f);
		ImGui::SliderFloat3("Attenuation", kAttenuation, 0.0f, 1.0f);
		m_pointLight.SetLightColor(ambient, diffuse, specular);
		m_pointLight.SetLightPosition(position);
		m_pointLight.SetLightAttenuation(kAttenuation[0], kAttenuation[1], kAttenuation[2]);
	}
}