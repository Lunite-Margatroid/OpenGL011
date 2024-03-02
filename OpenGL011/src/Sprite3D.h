#pragma once
#include "Sprite.h"
namespace LM
{
	class Sprite3D : public Sprite
	{
	protected:
		// ------------位姿---------------
		// -平移
		glm::vec3 m_Position;						// 偏移

		// -旋转
										// 转角 弧度制
		glm::vec3 m_RotationAxis;		// 转轴

		// -缩放
		glm::vec3 m_Scale;				//缩放

		

	public:
		Sprite3D(Shader* shader = nullptr, Camera* camera = nullptr, 
			const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
			float rotationRad = 0.0f,
			const glm::vec3& rotationAxis = glm::vec3(1.0f, 1.0f, 1.0f),
			const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)
			);
		virtual ~Sprite3D();

		// 设置uniform变量
		virtual void SetUniform() override;
		void SetUniform(const glm::mat4& objMoudleTrans = glm::mat4(1.0f));

		// 3D render
		virtual void Draw(const glm::mat4& objMoudleTrans = glm::mat4(1.0f)) override;
		// 2D render
		virtual void Draw(const glm::vec2& position = glm::vec2(1.0f, 1.0f), float rotationRad = 0.0f, const glm::vec2& scale = glm::vec2(1.0f, 1.0f)) override;

		// ---------- 平移 ----------

		virtual void SetPosition(const glm::vec3& position) override;
		virtual void SetPosition(const glm::vec2& position) override;
		virtual void Move(const glm::vec3& position) override;
		virtual void Move(const glm::vec2& position) override;
		virtual const glm::vec3& GetPosition() const override;
		virtual const glm::vec3& GetPosition3v() const override;
		virtual const glm::vec2& GetPosition2v() const override;

		// ------- 旋转 ------------
		virtual const glm::vec3& GetRotationAxis() const override;
		virtual void SetRotationAxis(const glm::vec3& rotationAxis) override;
		// --------- 缩放 ----------
		virtual void SetScale(const glm::vec3& scale) override;
		virtual void SetScale(const glm::vec2& scale) override;
		virtual const glm::vec3& GetScale3v() const override;
		virtual const glm::vec2& GetScale2v() const override;
		virtual void Scale(const glm::vec3& scale) override;
		virtual void Scale(const glm::vec2& scale) override;


	};
}