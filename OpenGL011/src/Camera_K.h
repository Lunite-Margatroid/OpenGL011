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
		void ProcessKeyInput(GLFWwindow* window, float deltaTime) override;
		void ProcessMouse(GLFWwindow* window, double xpos, double ypos) override;

		virtual void ProcessKeyInput(float deltaTime)override;
		virtual void ProcessMouse(float deltaTime)override;
	};

}