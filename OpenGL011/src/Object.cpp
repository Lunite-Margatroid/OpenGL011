#include "pch.h"
#include "Object.h"
namespace LM
{
	glm::vec3 Object::GetRotationAxis() const
	{
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}
	void Object::SetRotationAxis(const glm::vec3&)
	{
	}
}