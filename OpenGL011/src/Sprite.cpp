#include "pch.h"
#include "Sprite.h"

namespace LM
{
	Sprite::Sprite(Shader* shader, Camera* camera, float rotationRad)
		:m_Shader(shader), m_Camera(camera), m_RotationRad(rotationRad)
	{
	}
	Sprite::~Sprite()
	{
	}
	void Sprite::SetCamera(Camera* camera)
	{
		m_Camera = camera;
	}
	const Camera* Sprite::GetCamera() const
	{
		return m_Camera;
	}
	void Sprite::Draw(const glm::mat4& objMoudleTrans)
	{

	}
	void Sprite::Draw(const glm::vec2& position, float rotationRad, const glm::vec2& scale)
	{
	}
	void Sprite::SetShader(Shader* shader)
	{
		m_Shader = shader;
	}
	const Shader* Sprite::GetShader() const
	{
		return m_Shader;
	}
	void Sprite::AddMeshes(Mesh* mesh)
	{
		m_Meshes.push_back(mesh);
	}
	void Sprite::SetPosition(const glm::vec3& position)
	{
	}
	void Sprite::SetPosition(const glm::vec2& offset)
	{
	}
	void Sprite::Move(const glm::vec3& position)
	{
	}
	void Sprite::Move(const glm::vec2& position)
	{
	}
	const glm::vec3& Sprite::GetPosition() const
	{
		// TODO: 在此处插入 return 语句
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}
	const glm::vec3& Sprite::GetPosition3v() const
	{
		// TODO: 在此处插入 return 语句
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}
	const glm::vec2& Sprite::GetPosition2v() const
	{
		// TODO: 在此处插入 return 语句
		return glm::vec2(1.0f, 1.0f);
	}
	void Sprite::SetRotationRad(float rad)
	{
		m_RotationRad = rad;
	}
	float Sprite::GetRotationRad() const
	{
		return m_RotationRad;
	}
	void Sprite::Rotate(float rad)
	{
		m_RotationRad += rad;
	}
	const glm::vec3& Sprite::GetRotationAxis() const
	{
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}
	void Sprite::SetRotationAxis(const glm::vec3& rotationAxis)
	{

	}
	void Sprite::SetScale(const glm::vec3& scale)
	{
	}
	void Sprite::SetScale(const glm::vec2& scale)
	{
	}
	const glm::vec3& Sprite::GetScale3v() const
	{
		// TODO: 在此处插入 return 语句
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}
	const glm::vec2& Sprite::GetScale2v() const
	{
		// TODO: 在此处插入 return 语句
		return glm::vec2(1.0f, 1.0f);
	}
	void Sprite::Scale(const glm::vec3& scale)
	{
	}
	void Sprite::Scale(const glm::vec2& scale)
	{
	}
	bool Sprite::IsEnabled() const
	{
		return m_Enabled;
	}
	void Sprite::Enable()
	{
		m_Enabled = true;
	}
	void Sprite::Disable()
	{
		m_Enabled = false;
	}
}