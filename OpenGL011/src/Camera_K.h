#pragma once
#include "Camera.h"
namespace LM
{
	/// <summary>
	/// �����ƶ����̿��� ŷ����С���̿���
	/// </summary>
	class Camera_K :public Camera
	{
	public:
		Camera_K();
		~Camera_K();
		void ProcessKeyInput(GLFWwindow* window, float deltaTime);
		void ProcessMouse(GLFWwindow* window, double xpos, double ypos);
	};

}