#include "pch.h"
#include "Sprite3D.h"

namespace LM
{
	void Sprite3D::SetUniform()
	{
		glm::mat4 modelTrans = glm::mat4(1.0f);
		glm::mat4 viewTrans = glm::mat4(1.0f);
		glm::mat4 projectionTrans = glm::mat4(1.0f);

		
		modelTrans = glm::translate(modelTrans, m_Position);
		modelTrans = glm::rotate(modelTrans, m_RotationRad, m_Scale);
		modelTrans = glm::scale(modelTrans, m_Scale);

		viewTrans = m_Camera->GetViewTrans();
	}
	void Sprite3D::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}
	void Sprite3D::SetPosition(const glm::vec2& position)
	{
		m_Position.x = position.x;
		m_Position.y = position.y;
	}
	void Sprite3D::Move(const glm::vec3& position)
	{
		m_Position += position;
	}
	void Sprite3D::Move(const glm::vec2& position)
	{
		m_Position.x += position.x;
		m_Position.y += position.y;
	}
	const glm::vec3& Sprite3D::GetPosition() const
	{
		return m_Position;
	}
	const glm::vec3& Sprite3D::GetPosition3v() const
	{
		return m_Position;
	}
	const glm::vec2& Sprite3D::GetPosition2v() const
	{
		// TODO: 在此处插入 return 语句
		return glm::vec2(m_Position);
	}
	const glm::vec3& Sprite3D::GetRotationAxis() const
	{
		// TODO: 在此处插入 return 语句
		return m_RotationAxis;
	}
	void Sprite3D::SetRotationAxis(const glm::vec3& rotationAxis)
	{
		m_RotationAxis = rotationAxis;
	}
	void Sprite3D::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
	}
	void Sprite3D::SetScale(const glm::vec2& scale)
	{
		m_Scale.x = scale.x;
		m_Scale.y = scale.y;
	}
	const glm::vec3& Sprite3D::GetScale3v() const
	{
		return m_Scale;
	}
	const glm::vec2& Sprite3D::GetScale2v() const
	{
		return glm::vec2(m_Scale);
	}
	void Sprite3D::Scale(const glm::vec3& scale)
	{
		m_Scale = m_Scale * scale;
	}
	void Sprite3D::Scale(const glm::vec2& scale)
	{
		m_Scale.x *= scale.x;
		m_Scale.y *= scale.y;
	}
}
