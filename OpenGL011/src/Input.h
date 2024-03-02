#pragma once
namespace LM
{
	class Input
	{
	private:
		GLFWwindow* m_Window;
		static Input* s_Instance;
		static Input* GetInstance();
		Input();
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int mousecode);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static void SetWindow(GLFWwindow* window);
		static void FreeInstance();
	};
}
#define LM_INPUT_SET_WINDOW_PTR(x) LM::Input::SetWindow(x)
#define LM_INPUT_DESTROY LM::Input::FreeInstance()