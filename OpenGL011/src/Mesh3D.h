#pragma once
#include "Mesh.h"
namespace LM
{
	class Mesh3D : public Mesh
	{

		glm::vec3 m_Scale;
		glm::vec3 m_RotationAxis;

		glm::vec3 m_Postion;
	public:
		Mesh3D(VertexBuffer* vb, ElementBuffer* eb, VertexArray* va, glm::vec3 position,
			glm::vec3 rotationAxis, float rotationRad, glm::vec3 scale);
		virtual ~Mesh3D();
		virtual void SetUniform(Shader&, Camera&, const glm::mat4* parentModelTrans = NULL)override;
		void Init();
	};
}