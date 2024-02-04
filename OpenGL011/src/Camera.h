#pragma once


#ifndef PI
#define PI 3.14159f
#endif

namespace LM
{
	enum Camera_Movement
	{
		FRONT,
		BACK,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	// ��ʼֵ
	const float YAW = -PI / 2.0f;
	const float PITCH = 0.0f;
	const float SPEED = 5.0f;
	const float SCROLL_SENSITIVITY = 0.02f;
	const float ROTATE_SENEITIVITY = 0.005f;
	const float FOV = PI / 4.0f;

	/// <summary>
	/// Minecraft creative mode
	/// </summary>
	class Camera
	{
	protected:
		glm::vec3 m_position;		// �������λ�����������������
		glm::vec3 m_front;			// ������ĳ���z��ĸ����������������еķ���
		glm::vec3 m_up;				// ����������y������������������ķ���
		glm::vec3 m_right;			// ���������x������������������ķ���
		glm::vec3 m_worldUp;		// ��Ҫ���������� ���Ǹ���������

		float m_yaw;				// ת��Ϊy�� ����
		float m_pitch;				// ת��Ϊx�� ����

		float m_fov;				// ת��Ϊz�� Roll

		float m_moveSpeed;
		float m_scrollSensitivity;
		float m_rotateSensitivity;

		void UpdateViewTrans();
		void UpdateProjectionTrans();
		inline void CameraMove(Camera_Movement moveDir, float deltaTime);
		inline void CameraRotate(float yaw, float patch);
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW,
			float pitch = PITCH,
			float fov = FOV
		);

		void SetMoveSpeed(float moveSpeed);
		void SetScrollSensitivity(float sensitivity);
		void SetRotateSensitivity(float sensitivity);
		void SetFov(float fov);

		glm::mat4 GetViewTrans();
		glm::mat4 GetProjectionTrans();

		glm::vec3 GetPosition() const;
		glm::vec3 GetDirection() const;

		virtual void ProcessKeyInput(GLFWwindow* window, float deltaTime);
		virtual void ProcessMouse(GLFWwindow* window, double xpos, double ypos);
		virtual void ProcessScroll(float offsety);

	};
}