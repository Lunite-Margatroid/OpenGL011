#include "pch.h"
#include "Camera_K.h"

LM::Camera_K::Camera_K()
{
	Camera::SetRotateSensitivity(1.0f);
}

LM::Camera_K::~Camera_K()
{
}

void LM::Camera_K::ProcessKeyInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraMove(LM::FRONT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraMove(LM::BACK, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraMove(LM::LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraMove(LM::RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		CameraMove(LM::UP, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		CameraMove(LM::DOWN, deltaTime);
	}

	float yaw = 0.0f, pitch = 0.0f;
	float deltaRad = PI/2 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		yaw += deltaRad;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		yaw -= deltaRad;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		pitch += deltaRad;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
	{
		pitch -= deltaRad;
	}
	CameraRotate(yaw, pitch);
}

void LM::Camera_K::ProcessMouse(GLFWwindow* window, double xpos, double ypos)
{
}

void LM::Camera_K::ProcessKeyInput(float deltaTime)
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		CameraMove(LM::FRONT, deltaTime);
	}

	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		CameraMove(LM::BACK, deltaTime);
	}

	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		CameraMove(LM::LEFT, deltaTime);
	}

	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		CameraMove(LM::RIGHT, deltaTime);
	}

	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		CameraMove(LM::UP, deltaTime);
	}

	if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		CameraMove(LM::DOWN, deltaTime);
	}

	float yaw = 0.0f, pitch = 0.0f;
	float deltaRad = PI / 2 * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_KP_6))
	{
		yaw += deltaRad;
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_4))
	{
		yaw -= deltaRad;
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_8))
	{
		pitch += deltaRad;
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_2))
	{
		pitch -= deltaRad;
	}

	if (Input::IsKeyPressed(GLFW_KEY_KP_ADD))
	{
		m_fov -= deltaTime * m_keyFovSensitivity;
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_SUBTRACT))
	{
		m_fov += deltaTime * m_keyFovSensitivity;
	}
	if (m_fov > PI / 4.0f)
		m_fov = PI / 4.0f;
	if (m_fov < 0.02f)
		m_fov = 0.02f;

	CameraRotate(yaw, pitch);
}

void LM::Camera_K::ProcessMouse(float deltaTime)
{
}
