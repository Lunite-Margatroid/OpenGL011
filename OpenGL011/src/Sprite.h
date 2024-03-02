#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
namespace LM {
	class Sprite
	{
	protected:
		const Shader* m_Shader;
		const Camera* m_Camera;
		bool m_Enabled;

		// ------------λ��---------------
		// -ƽ��
								// ƫ��
								
		// -��ת
		float m_RotationRad;	// ת�� ������
								// ת��

		// -����
								//����
		


		// Meshes
		std::vector<Mesh*> m_Meshes;
		Sprite(Shader* shader = nullptr,Camera* camera = nullptr, float rotationRad = 0.0f);
		
	public:
		virtual ~Sprite();

		// ����uniform����
		virtual void SetUniform() = 0;
		
		virtual void SetCamera(Camera* camera);
		virtual const Camera* GetCamera() const;

		// 3D render
		virtual void Draw(const glm::mat4& objMoudleTrans = glm::mat4(1.0f));
		// 2D render
		virtual void Draw(const glm::vec2& position = glm::vec2(1.0f, 1.0f), float rotationRad = 0.0f, const glm::vec2& scale = glm::vec2(1.0f, 1.0f));

		virtual void SetShader(Shader* shader);
		virtual const Shader* GetShader() const;

		virtual void AddMeshes(Mesh* mesh);
		// ---------- ƽ�� ----------
		virtual void SetPosition(const glm::vec3& position);
		virtual void SetPosition(const glm::vec2& offset);
		virtual void Move(const glm::vec3& position); 
		virtual void Move(const glm::vec2& position);
		virtual const glm::vec3& GetPosition() const;
		virtual const glm::vec3& GetPosition3v() const;
		virtual const glm::vec2& GetPosition2v() const;


		// ------- ��ת ------------
		// ������ת�Ƕ�
		void SetRotationRad(float rad);
		// �����ת�Ƕ�
		float GetRotationRad() const;
		// ��ת�Ƕ�����rad
		void Rotate(float rad);
		// ��ת��
		virtual const glm::vec3& GetRotationAxis() const;
		virtual void SetRotationAxis(const glm::vec3& rotationAxis); // 2D�������������
		// --------- ���� ----------
		virtual void SetScale(const glm::vec3& scale);
		virtual void SetScale(const glm::vec2& scale);
		virtual const glm::vec3& GetScale3v() const;
		virtual const glm::vec2& GetScale2v() const;
		virtual void Scale(const glm::vec3& scale);
		virtual void Scale(const glm::vec2& scale);
		

		//----------����-------------
		bool IsEnabled() const;
		void Enable();
		void Disable();
	};
}
