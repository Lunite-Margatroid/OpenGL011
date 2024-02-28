#include "pch.h"
#include "TestMesh3D.h"
extern LM::Camera_K& pCamera;

namespace test
{
	TestMesh3D::TestMesh3D() :
		m_shader("./res/shader/3DDirLightVertex.shader", "./res/shader/3D_PNT_DL1_Phong_F.shader"),
		m_shaderShadowTex("./res/shader/ShadowTexVertex.shader", "./res/shader/ShadowTexFrag.shader"),
		m_shaderShadowed("./res/shader/DirLightShadowVertex.shader", "./res/shader/3D_PNT_DL1_Shadow_Phong_F.shader"),
		m_texFloor("./res/img/floor2.jpg", 0, GL_RGB, GL_RGB),
		m_texCube("./res/img/img_2.png", 1, GL_RGBA, GL_RGBA),
		m_floorShininess(16.0f),
		m_cubeShininess(32.0f),
		m_shaderDraw(&m_shaderShadowed),
		m_depthMap(1024, 1024, 2),
		m_shadow(true)
	{
		//------------------- 初始化--------------------
		m_lightDirection = glm::vec3(0.2f, -1.0f, 0.0f);
		m_dirLight.SetLightDirection(m_lightDirection);
		m_ambient = m_dirLight.GetAmbient();
		m_specular = m_dirLight.GetSpecular();
		m_diffuse = m_dirLight.GetDiffuse();

		m_cubeRotation[0] = glm::vec4(0.0f);
		m_cubeRotation[0].y = 1.0f;
		m_cubeRotation[1] = glm::vec4(0.0f);
		m_cubeRotation[1].y = 1.0f;

		m_cubePosition[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cubePosition[1] = glm::vec3(0.0f, 2.5f, -3.0f);

		m_cubeShininess = m_meshCube.GetShininess();
		m_floorShininess = m_meshFloor.GetShininess();
		//---------------------------------------------
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
		float cubeVertice[] =
		{
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
				1.0f, 0.0f, 0.0f,			1.0f, 0.0f, 0.0f,		0.0f, 1.0f
		};
		float floorVertice[] =
		{
			// 位置坐标					法线向量					纹理坐标
				//--------------- 地板 -----------------------
				-50.0f, 0.0f, -50.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
				50.0f, 0.0f, -50.0f,		0.0f, 1.0f, 0.0f,		20.0f, 0.0f,
				50.0f, 0.0f, 50.0f,			0.0f, 1.0f, 0.0f,		20.0f, 20.0f,
				-50.0f, 0.0f, 50.0f,		0.0f, 1.0f, 0.0f,		0.0f, 20.0f
		};
		
		unsigned int cubeIndice[36];
		cubeIndice[0] = 0;
		cubeIndice[1] = 1;
		cubeIndice[2] = 2;
		cubeIndice[3] = 2;
		cubeIndice[4] = 3;
		cubeIndice[5] = 0;
		for (int i = 6; i < 36; i++)
			cubeIndice[i] = cubeIndice[i - 6] + 4;
		unsigned int floorIndice[] =
		{ 0, 1, 2,2,3 ,0};
		// -------地板---------
		m_vbo[0].Init(sizeof(floorVertice), floorVertice);
		m_ebo[0].Init(sizeof(floorIndice) / sizeof(unsigned int), floorIndice);
		m_vao[0].SetVB(&m_vbo[0]);
		m_vao[0].SetEB(&m_ebo[0]);
		m_vao[0].Bind();
		m_vao[0].PushAttrib<float>(3);
		m_vao[0].PushAttrib<float>(3);
		m_vao[0].PushAttrib<float>(2);
		m_vao[0].ApplyLayout();
		m_vao[0].SetMetaType(GL_TRIANGLES);

		// -------cube---------
		m_vbo[1].Init(sizeof(cubeVertice), cubeVertice);
		m_ebo[1].Init(36, cubeIndice);
		m_vao[1].Bind();
		m_vao[1].SetVB(&m_vbo[1]);
		m_vao[1].SetEB(&m_ebo[1]);
		m_vao[1].PushAttrib<float>(3);
		m_vao[1].PushAttrib<float>(3);
		m_vao[1].PushAttrib<float>(2);
		m_vao[1].ApplyLayout();
		

		m_meshFloor.Init(&m_vao[0]);
		m_meshFloor.PushTexture(&m_texFloor);

		m_meshCube.Init(&m_vao[1]);
		m_meshCube.PushTexture(&m_texCube);

		// 开启混合
		GLCall(glEnable(GL_BLEND));
		// 无视alpha通道 完全遮挡
		GLCall(glBlendFunc(GL_ONE, GL_ZERO));
		glEnable(GL_DEPTH_TEST);
	}

	TestMesh3D::~TestMesh3D()
	{
		GLCall(glDisable(GL_BLEND));
		glDisable(GL_DEPTH_TEST);
	}
	void TestMesh3D::OnRender()
	{
		// 声明静态变量
		static glm::mat4 modelTrans(1.0f);
		static glm::mat4 viewTrans;
		static glm::mat4 projectionTrans;
		static glm::mat3 normalMat;
		static glm::vec3 cameraPos;
		static glm::mat4 lightTrans;
		static glm::mat4 lightView;
		static glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 15.0f);
		static glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
		// 更新静态变量
		viewTrans = pCamera.GetViewTrans();
		projectionTrans = pCamera.GetProjectionTrans();
		cameraPos = pCamera.GetPosition();

		
		// 绘制深度贴图
		{
			m_depthMap.Bind();	// 绑定帧缓冲
			GLCall(glClear(GL_DEPTH_BUFFER_BIT));
			glViewport(0, 0, m_depthMap.GetWidth(), m_depthMap.GetHeight());
			m_shaderShadowTex.Bind();
			lightView = glm::lookAt(lightPos, lightPos + m_dirLight.GetDirection(), glm::vec3(0.0f, 1.0f, 0.0f));
			lightTrans = lightProjection * lightView;
			modelTrans = glm::mat4(1.0f);
			m_shaderShadowTex.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
			m_shaderShadowTex.SetUniformMatrix4f("u_lightTrans", false, glm::value_ptr(lightTrans));
			m_meshFloor.Draw(m_shaderShadowTex);													// 地板

			modelTrans = glm::translate(glm::mat4(1.0f), m_cubePosition[0]);
			modelTrans = glm::rotate(modelTrans, m_cubeRotation[0].w, glm::vec3(m_cubeRotation[0]));
			m_shaderShadowTex.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
			m_meshCube.Draw(m_shaderShadowTex);// cube1

			modelTrans = glm::translate(glm::mat4(1.0f), m_cubePosition[1]);
			modelTrans = glm::rotate(modelTrans, m_cubeRotation[1].w, glm::vec3(m_cubeRotation[1]));
			m_shaderShadowTex.SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
			m_meshCube.Draw(m_shaderShadowTex);// cube2

			// 绑定默认帧缓冲
			m_depthMap.Unbind();
		}
		// 绘制main
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, WIDTH, HEIGHT);
		m_shaderDraw->Bind();
		if (m_shadow)
		{
			m_shaderDraw->SetUniformTexture("u_depthMap", m_depthMap.GetTexIndex());
			m_shaderDraw->SetUniformMatrix4f("u_lightTrans", false, glm::value_ptr(lightTrans));
		}
		m_shaderDraw->SetUniformMatrix4f("u_viewTrans", false, glm::value_ptr(viewTrans));
		m_shaderDraw->SetUniformMatrix4f("u_projectionTrans", false, glm::value_ptr(projectionTrans));

		m_shaderDraw->SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
		

		m_dirLight.SetUniformLight("u_dirLight", *m_shaderDraw);

		m_dirLight.SetLightColor(m_ambient, m_diffuse, m_specular);
		m_dirLight.SetLightDirection(m_lightDirection);

		
		modelTrans = glm::mat4(1.0f);
		normalMat = glm::transpose(inverse(modelTrans));
		m_shaderDraw->SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shaderDraw->SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));
		m_meshFloor.Draw(*m_shaderDraw);

		modelTrans = glm::translate(glm::mat4(1.0f), m_cubePosition[0]);
		modelTrans = glm::rotate(modelTrans, m_cubeRotation[0].w, glm::vec3(m_cubeRotation[0]));
		normalMat = glm::transpose(inverse(modelTrans));
		m_shaderDraw->SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shaderDraw->SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));

		m_meshCube.Draw(*m_shaderDraw);

		modelTrans = glm::translate(glm::mat4(1.0f), m_cubePosition[1]);
		modelTrans = glm::rotate(modelTrans, m_cubeRotation[1].w, glm::vec3(m_cubeRotation[1]));
		normalMat = glm::transpose(inverse(modelTrans));
		m_shaderDraw->SetUniformMatrix4f("u_modelTrans", false, glm::value_ptr(modelTrans));
		m_shaderDraw->SetUniformMatrix3f("u_normalMat", false, glm::value_ptr(normalMat));

		m_meshCube.Draw(*m_shaderDraw);
	}
	void TestMesh3D::OnUpdate(float deltaTime)
	{
		if (m_shadow)
			m_shaderDraw = &m_shaderShadowed;
		else
			m_shaderDraw = &m_shader;

		m_meshCube.SetShininess(m_cubeShininess);
		m_meshFloor.SetShininess(m_floorShininess);
	}
	void TestMesh3D::OnRenderImgui()
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

		ImGui::Checkbox("shadow", &m_shadow);
	}
}