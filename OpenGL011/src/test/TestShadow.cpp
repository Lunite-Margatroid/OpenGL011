#include "pch.h"
#include "TestShadow.h"
extern LM::Camera_K& pCamera;

namespace test
{
	TestShadow::TestShadow() :
		m_shader("./res/shader/3DDirLightShadowVertex.shader", "./res/shader/3DDirLightShadowFrag.shader"),
		m_texFloor("./res/img/floor2.jpg", 0, GL_RGB, GL_RGB),
		m_texCube("./res/img/img_2.png", 1, GL_RGBA, GL_RGBA),
		m_floorShininess(16.0f),
		m_cubeShininess(32.0f)
	{
		m_lightDirection = m_dirLight.GetDirection();
		m_ambient = m_dirLight.GetAmbient();
		m_specular = m_dirLight.GetSpecular();
		m_diffuse = m_dirLight.GetDiffuse();

		m_cubeRotation[0] = glm::vec4(0.0f);
		m_cubeRotation[0].y = 1.0f;
		m_cubeRotation[1] = glm::vec4(0.0f);
		m_cubeRotation[1].y = 1.0f;

		float vertice[] =
		{	// 位置坐标					法线向量					纹理坐标
			//--------------- 地板 -----------------------
			-50.0f, 0.0f, -50.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
			50.0f, 0.0f, -50.0f,		0.0f, 1.0f, 0.0f,		20.0f, 0.0f,
			50.0f, 0.0f, 50.0f,			0.0f, 1.0f, 0.0f,		20.0f, 20.0f,
			-50.0f, 0.0f, 50.0f,		0.0f, 1.0f, 0.0f,		0.0f, 20.0f,
			//--------------- cube ----------------------
			-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			0.0f, 0.0f,
			1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,			0.0f, 1.0f,

			-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,			0.0f, 0.0f,
			-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			1.0f, 0.0f,
			1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,			0.0f, 1.0f,

			-1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,			0.0f, 0.0f,
			-1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,			1.0f, 0.0f,
			1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,			1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,			0.0f, 1.0f,

			-1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,			0.0f, 0.0f,
			1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,			1.0f, 0.0f,
			1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,			1.0f, 1.0f,
			-1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,			0.0f, 1.0f,

			1.0f,-1.0f, -1.0f,		1.0f, 0.0f,  0.0f,			0.0f, 0.0f,
			1.0f,1.0f, -1.0f,		1.0f, 0.0f,  0.0f,			1.0f, 0.0f,
			1.0f,1.0f, 1.0f,		1.0f, 0.0f,  0.0f,			1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,		1.0f, 0.0f,  0.0f,			0.0f, 1.0f,

			-1.0f,-1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,			0.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,			1.0f, 0.0f,
			-1.0f,1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,			1.0f, 1.0f,
			-1.0f,1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,			0.0f, 1.0f,

			-1.0f, -1.0f, -1.0f,		0.0f, -1.0f, 0.0f,		0.0f, 0.0f,
			1.0f, -1.0f, -1.0f,			0.0f, -1.0f, 0.0f,		1.0f, 0.0f,
			1.0f, -1.0f, 1.0f,			0.0f, -1.0f, 0.0f,		1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,			0.0f, -1.0f, 0.0f,		0.0f, 1.0f,

			-1.0f, 1.0f, -1.0f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
			1.0f, 1.0f, -1.0f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,

			0.0f,0.0f, -1.0f,			0.0f,0.0f, -1.0f,		0.0f, 0.0f,
			0.0f,0.0f, -1.0f,			0.0f,0.0f, -1.0f,		1.0f, 0.0f,
			0.0f,0.0f, -1.0f,			0.0f,0.0f, -1.0f,		1.0f, 1.0f,
			0.0f,0.0f, -1.0f,			0.0f,0.0f, -1.0f,		0.0f, 1.0f,

			0.0f,0.0f, 1.0f,			0.0f,0.0f, 1.0f,		0.0f, 0.0f,
			0.0f,0.0f, 1.0f,			0.0f,0.0f, 1.0f,		1.0f, 0.0f,
			0.0f,0.0f, 1.0f,			0.0f,0.0f, 1.0f,		1.0f, 1.0f,
			0.0f,0.0f, 1.0f,			0.0f,0.0f, 1.0f,		0.0f, 1.0f,

			-1.0f, 0.0f,0.0f,			-1.0f, 0.0f,0.0f,		0.0f, 0.0f,
			-1.0f, 0.0f,0.0f,			-1.0f, 0.0f,0.0f,		1.0f, 0.0f,
			-1.0f, 0.0f,0.0f,			-1.0f, 0.0f,0.0f,		1.0f, 1.0f,
			-1.0f, 0.0f,0.0f,			-1.0f, 0.0f,0.0f,		0.0f, 1.0f,

			1.0f, 0.0f, 0.0f,			1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,			1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,			1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
			1.0f, 0.0f, 0.0f,			1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		};
		unsigned int indice[40] = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 4 };
		for (unsigned int i = 10; i < 40; i++)
		{
			indice[i] = indice[i - 6] + 4;
		}

		m_vbo.Init(sizeof(vertice), vertice);
		m_ebo.Init(40, indice);
		m_vao.Bind();
		m_vao.PushAttrib<float>(3);
		m_vao.PushAttrib<float>(3);
		m_vao.PushAttrib<float>(2);
		m_vao.ApplyLayout();

		// 开启混合
		GLCall(glEnable(GL_BLEND));
		// 无视alpha通道 完全遮挡
		GLCall(glBlendFunc(GL_ONE, GL_ZERO));
		glEnable(GL_DEPTH_TEST);
	}

	TestShadow::~TestShadow()
	{
		GLCall(glDisable(GL_BLEND));
		glDisable(GL_DEPTH_TEST);
	}
	void TestShadow::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		static glm::mat4 modelTrans(1.0f);
		static glm::mat4 viewTrans;
		static glm::mat4 projectionTrans;
		static glm::mat3 normalMat;
		static glm::vec3 cameraPos;
		viewTrans = pCamera.GetViewTrans();
		projectionTrans = pCamera.GetProjectionTrans();
		cameraPos = pCamera.GetPosition();
		m_shader.Bind();
		m_shader.SetUniformMatrix4f("u_viewTrans", false, glm::value_ptr(viewTrans));
		m_shader.SetUniformMatrix4f("u_projectionTrans", false, glm::value_ptr(projectionTrans));

		m_shader.SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
		m_shader.SetUniform1f("u_material.shininess", 20.0f);
		m_shader.SetUniformTexture("u_material.texture_diffuse1", m_texFloor.GetIndex());
		m_shader.SetUniformTexture("u_material.texture_diffuse2", m_texCube.GetIndex());

		m_dirLight.SetUniformLight("u_dirLight", m_shader);

		m_dirLight.SetLightColor(m_ambient, m_diffuse, m_specular);
		m_dirLight.SetLightDirection(m_lightDirection);

		m_vao.Bind();
		
		m_shader.SetUniform1i("u_texID", 0);
		m_shader.SetUniform1f("u_material.shininess", m_floorShininess);
		modelTrans = glm::mat4(1.0f);
		normalMat = glm::transpose(inverse(modelTrans));
		m_shader.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shader.SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));
		GLCall(glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0));

		m_shader.SetUniform1i("u_texID", 1);
		m_shader.SetUniform1f("u_material.shininess", m_cubeShininess);

		modelTrans = glm::translate(glm::mat4(1.0f), m_cubePosition[0]);
		modelTrans = glm::rotate(modelTrans, m_cubeRotation[0].w, glm::vec3(m_cubeRotation[0]));
		normalMat = glm::transpose(inverse(modelTrans));
		m_shader.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shader.SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));

		GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(4 * sizeof(unsigned int))));

		modelTrans = glm::translate(glm::mat4(1.0f), m_cubePosition[1]);
		modelTrans = glm::rotate(modelTrans, m_cubeRotation[1].w, glm::vec3(m_cubeRotation[1]));
		normalMat = glm::transpose(inverse(modelTrans));
		m_shader.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shader.SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));

		GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(4 * sizeof(unsigned int))));
	}
	void TestShadow::OnUpdate(float deltaTime)
	{
		
	}
	void TestShadow::OnRenderImgui()
	{
		ImGui::SliderFloat3("lightDirection", &m_lightDirection.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("ambient", &m_ambient.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("diffuse", &m_diffuse.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("specular", &m_specular.x, 0.0f, 1.0f);
		ImGui::SliderFloat("FloorShininess", &m_floorShininess, 0.0f, 64.0f);
		ImGui::SliderFloat("CubeShininess", &m_cubeShininess, 0.0f, 64.0f);

		ImGui::Text("Cube1");
		ImGui::SliderFloat3("Cube1 Position", &m_cubePosition[0].x, -5.0f, 5.0f);
		ImGui::SliderFloat("Cube1 Rotation Angle", &m_cubeRotation[0].w, -PI, PI);
		ImGui::SliderFloat3("Cube1 Rotation Axis", &m_cubeRotation[0].x, -1.0f, 1.0f);
		
		ImGui::Text("Cube2");
		ImGui::SliderFloat3("Cube2 Position", &m_cubePosition[1].x, -5.0f, 5.0f);
		ImGui::SliderFloat("Cube2 Rotation Angle", &m_cubeRotation[1].w, -PI, PI);
		ImGui::SliderFloat3("Cube2 Rotation Axis", &m_cubeRotation[1].x, -1.0f, 1.0f);
	}
}