#include "pch.h"
#include "Test3D.h"

extern LM::Camera_K& pCamera;

namespace test
{
	Test3D::Test3D() :
		m_shader("./res/shader/3DVertex.shader", "./res/shader/3DFragment.shader"),
		m_texture("./res/img/floor2.jpg", 0, GL_RGB, GL_RGB)
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
	}
	void Test3D::OnUpdate(float deltaTime)
	{
		static glm::mat4 modelTrans(1.0f);
		static glm::mat4 viewTrans(1.0f);
		static glm::mat4 projectionTrans(1.0f);
		static glm::mat4 normalTrans(1.0f);
		viewTrans = pCamera.GetViewTrans();
		projectionTrans = pCamera.GetProjectionTrans();
		normalTrans = glm::mat3(transpose(inverse(modelTrans)));

		m_shader.Bind();
		m_shader.SetUniformModelTrans(modelTrans);
		m_shader.SetUniformViewTrans(viewTrans);
		m_shader.SetUniformProjectionTrans(projectionTrans);
	}
	void Test3D::OnRender()
	{
		m_shader.Bind();
		m_vao.Bind();
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
	}
	void Test3D::OnRenderImgui()
	{
		glm::vec3 v3Position = pCamera.GetPosition();
		glm::vec3 v3Direction = pCamera.GetDirection();
		ImGui::Text("Camera Position: (%.3f, %.3f, %.3f)", v3Position.x, v3Position.y, v3Position.z);
		ImGui::Text("Camera heads: (%.3f, %.3f, %.3f)", v3Direction.x, v3Direction.y, v3Direction.z);
		ImGui::Text("yaw: %.3f, pitch: %.3f, fov: %.3f", pCamera.GetYaw(), pCamera.GetPitch(), pCamera.GetFov());
	}
}