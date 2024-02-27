#include "pch.h"
#include "Mesh3D.h"

namespace LM
{
	Mesh3D::Mesh3D(VertexBuffer* vb, ElementBuffer* eb, VertexArray* va, 
		glm::vec3 position = glm::vec3(1.0f),
		glm::vec3 rotationAxis = glm::vec3(1.0f), 
		float rotationRad = 0.0f, 
		glm::vec3 scale = glm::vec3(1.0f))
		:Mesh(vb, eb, va, rotationRad), m_Postion(position), m_RotationAxis(rotationAxis),m_Scale(scale)
	{
	}
	Mesh3D::~Mesh3D()
	{
	}
	void Mesh3D::SetUniform(Shader&, Camera&, const glm::mat4* parentModelTrans)
	{
	}
	void Mesh3D::Init()
	{
	}
}