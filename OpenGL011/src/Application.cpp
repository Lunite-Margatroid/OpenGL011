#include "pch.h"
#include "Init.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Quad.h"
#include "Camera_K.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include "test/TestQuadA.h"
#include "test/TestClearColor.h"
#include "test/Test3D.h"
#include "test/TestBlinn.h"

void UpdateTimer();
void RuntimeLog();
void ProcessInput(GLFWwindow* window);
// 全局变量
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

LM::Camera_K camera;
extern LM::Camera_K& pCamera = camera;

int main()
{
	GLFWwindow* window = InitGL();

	/* Setup Dear ImGui context */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	// Our state

	ImGui_ImplOpenGL3_Init("#version 130");
	{
		test::TestQuadA test;
		test::TestClearColor testClearColor;

		test::Test* pTest = nullptr;
		test::TestMenu testMenu(pTest);    
		test::Test* pTestMenu = &testMenu;
		pTest = pTestMenu;

		testMenu.RegisterTest<test::TestQuadA>("testQuadA");
		testMenu.RegisterTest<test::TestClearColor>("TestClearColor");
		testMenu.RegisterTest<test::Test3D>("Test 3D");
		testMenu.RegisterTest<test::TestBlinn>("Test Bilnn-Phong");
		while (!glfwWindowShouldClose(window))
		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			// OnRenderImgui
			{
				ImGui::Begin("Test");

				if (pTest != pTestMenu && ImGui::Button("<-"))
				{
					delete pTest;
					pTest = pTestMenu;
				}
				pTest->OnRenderImgui();
				ImGui::End();
			}
			// OnUpdate
			{
				pTest->OnUpdate(deltaTime);
			}

			
			// Rendering
			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			GLCall(glViewport(0, 0, display_w, display_h));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			{/* Render Here */
				pTest->OnRender();
				
			/***************/
			}
			// 这个大概是绘制imgui的窗口的
			// 之前的那一大堆应该是准备数据
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			

			// 交换缓冲
			glfwSwapBuffers(window);
			// 处理输入
			ProcessInput(window);
			// log 输出当前摄像机坐标
			RuntimeLog();
			// 更新时间变量
			UpdateTimer();
			// 检查触发事件
			glfwPollEvents();
		}
		// testMenu在栈区
		// 动态创建的测试在堆区
		if (pTest != pTestMenu)
		{
			delete pTest;
		}
		
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	// 检测esc按下，则关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	camera.ProcessKeyInput(window, deltaTime);
}


void UpdateTimer()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

void RuntimeLog()
{
	static glm::vec3 cameraPos = camera.GetPosition();
	cameraPos = camera.GetPosition();

	std::cout << "Camera current position:" << '(' << cameraPos.x << ',' << cameraPos.y
		<< ',' << cameraPos.z << ")                " << std::endl;

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO cursorInfo;
	GetConsoleScreenBufferInfo(hOut, &cursorInfo);
	coord = cursorInfo.dwCursorPosition;
	coord.X = 0;
	coord.Y -= 1;
	SetConsoleCursorPosition(hOut, coord);
}