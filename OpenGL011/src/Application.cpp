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

void UpdateTimer();
void RuntimeLog();
void ProcessInput(GLFWwindow* window);
// 全局变量
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

LM::Camera_K camera;

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
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui_ImplOpenGL3_Init("#version 130");
	{

		/*unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));*/

		LM::Texture tex("./res/img/img_1.jpg", 0, GL_RGB, GL_RGB);

		LM::Quad quad(1.0f, 1.0f);
		LM::Quad quadTex(tex, true);

		LM::VertexArray va;

		float vertice[] =
		{
			0.5f, 0.5f,
			-0.5f, 0.5f,
			-0.5f, -0.5f,
			0.5f, -0.5f
		};
		LM::VertexBuffer vb(sizeof(vertice), vertice);



		unsigned int  indice[] =
		{
			0,1,2,
			2,3,0
		};
		LM::ElementBuffer eb(4, indice);

		glm::mat4 proj = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f,1.0f);
		glm::mat4 modelTrans = glm::scale(glm::mat4(1.0f), glm::vec3(9.0f, 9.0f, 0.0f));
		glm::vec3 position(0.0f);
		modelTrans = glm::translate(modelTrans, position);
		//modelTrans = glm::rotate(modelTrans, PI / 4, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mvp = proj * modelTrans;
		va.PushAttrib<float>(2);
		va.ApplyLayout();
		LM::Shader shader("./res/shader/VertexShader.shader", "./res/shader/FragmentShader.shader");
		LM::Shader shaderTex("./res/shader/TexVertexShader.shader","./res/shader/TexFragmentShader.shader");

		while (!glfwWindowShouldClose(window))
		{
			
			

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if (true)
				ImGui::ShowDemoWindow(&show_demo_window);

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			{
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &position[0], -4.0f, 4.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			// 3. Show another simple window.
			if (show_another_window)
			{
				ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				ImGui::Text("Hello from another window!");
				if (ImGui::Button("Close Me"))
					show_another_window = false;
				ImGui::End();
			}

			// Rendering
			
			

			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);
			/* Render Here */
			//shader.Bind();
			modelTrans = glm::translate(glm::mat4(1.0f), position);
			modelTrans = glm::scale(modelTrans, glm::vec3(9.0f, 9.0f, 0.0f));
			mvp = proj * modelTrans;
			shaderTex.Bind();
			shaderTex.SetUniformMatrix4f("u_mvp", false, glm::value_ptr(mvp));
			quadTex.Draw();
			//va.Bind();
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			/***************/
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			


			glfwSwapBuffers(window);
			// 处理输入
			ProcessInput(window);
			// log
			RuntimeLog();
			// 更新时间变量
			UpdateTimer();
			// 检查触发事件
			glfwPollEvents();
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