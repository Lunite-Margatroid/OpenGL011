#pragma once
#include "Camera.h"
namespace LM
{
	/// <summary>
	/// 坐标移动键盘控制 欧拉角小键盘控制
	/// </summary>
	class Camera_K :public Camera
	{
	public:
		Camera_K();
		~Camera_K();
		void ProcessKeyInput(GLFWwindow* window, float deltaTime) override;
		void ProcessMouse(GLFWwindow* window, double xpos, double ypos) override;

		virtual void ProcessKeyInput(float deltaTime)override;
		virtual void ProcessMouse(float deltaTime)override;
	};

}