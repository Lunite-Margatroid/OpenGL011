#pragma once
#include "Sprite.h"
namespace LM
{
	class Sprite3D : public Sprite
	{
	protected:
		// ------------λ��---------------
		// -ƽ��
		glm::vec3 m_Position;						// ƫ��

		// -��ת
										// ת�� ������
		glm::vec3 m_RotationAxis;		// ת��

		// -����
		glm::vec3 m_Scale;				//����

		

	public:
		Sprite3D(Shader* shader = nullptr, Camera* camera = nullptr, 
			const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
			float rotationRad = 0.0f,
			const glm::vec3& rotationAxis = glm::vec3(1.0f, 1.0f, 1.0f),
			const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)
			);
		virtual ~Sprite3D();

		// ����uniform����
		virtual void SetUniform() override;
		void SetUniform(const glm::mat4& objMoudleTrans = glm::mat4(1.0f));

		// 3D render
		virtual void Draw(const glm::mat4& objMoudleTrans = glm::mat4(1.0f)) override;
		// 2D render
		virtual void Draw(const glm::vec2& position = glm::vec2(1.0f, 1.0f), float rotationRad = 0.0f, const glm::vec2& scale = glm::vec2(1.0f, 1.0f)) override;

		// ---------- ƽ�� ----------

		virtual void SetPosition(const glm::vec3& position) override;
		virtual void SetPosition(const glm::vec2& position) override;
		virtual void Move(const glm::vec3& position) override;
		virtual void Move(const glm::vec2& position) override;
		virtual const glm::vec3& GetPosition() const override;
		virtual const glm::vec3& GetPosition3v() const override;
		virtual const glm::vec2& GetPosition2v() const override;

		// ------- ��ת ------------
		virtual const glm::vec3& GetRotationAxis() const override;
		virtual void SetRotationAxis(const glm::vec3& rotationAxis) override;
		// --------- ���� ----------
		virtual void SetScale(const glm::vec3& scale) override;
		virtual void SetScale(const glm::vec2& scale) override;
		virtual const glm::vec3& GetScale3v() const override;
		virtual const glm::vec2& GetScale2v() const override;
		virtual void Scale(const glm::vec3& scale) override;
		virtual void Scale(const glm::vec2& scale) override;


	};
}