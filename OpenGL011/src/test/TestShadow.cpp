#include "pch.h"
#include "TestShadow.h"
extern LM::Camera_K& pCamera;

namespace test
{
	TestShadow::TestShadow() :
		m_shader("./res/shader/3DDirLightShadowVertex.shader", "./res/shader/3DDirLightShadowFrag.shader"),
		m_texFloor("./res/img/floor2.jpg",0, GL_RGB, GL_RGB),
		m_texCube("./res/img/img_2.png",1, GL_RGBA, GL_RGBA)
	{
		m_lightDirection = m_dirLight.GetDirection();
		m_ambient = m_dirLight.GetAmbient();
		m_specular = m_dirLight.GetSpecular();
		m_diffuse = m_dirLight.GetDiffuse();


		memset(m_cubePos, 0, sizeof(float) * 6);

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
		unsigned int indice[40] = {0, 1, 2, 3, 4, 5, 6, 6, 7, 4};
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
	}

	TestShadow::~TestShadow()
	{
		GLCall(glDisable(GL_BLEND));
	}
	void TestShadow::OnRender()
	{
		m_vao.Bind();
		m_shader.Bind();
		glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
		glDrawElementsInstanced(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)(4*sizeof(unsigned int)), 2);
	}
	void TestShadow::OnUpdate(float deltaTime)
	{
		static glm::mat4 modelTrans(1.0f);
		static glm::mat4 viewTrans;
		static glm::mat4 projectionTrans;
		static glm::mat3 normalMat;
		static glm::vec3 cameraPos;
		viewTrans = pCamera.GetViewTrans();
		projectionTrans = pCamera.GetProjectionTrans();
		normalMat = glm::transpose(inverse(modelTrans));
		cameraPos = pCamera.GetPosition();
		m_shader.Bind();
		m_shader.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shader.SetUniformMatrix4f("u_viewTrans", false, glm::value_ptr(viewTrans));
		m_shader.SetUniformMatrix4f("u_projectionTrans", false, glm::value_ptr(projectionTrans));
		m_shader.SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));

		m_shader.SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
		
	}
}