#pragma once
#include "Mesh.h"
namespace LM
{
	class Mesh3D : public Mesh
	{
	protected:
		float m_shininiess;

		virtual void SetUniformTexture(Shader& shader)override;
	public:
		Mesh3D(VertexArray* va, float shininess = 16.0f);
		Mesh3D(float shininess = 16.0f);
		virtual ~Mesh3D();
		
		void Init(VertexArray* va);
		float GetShininess() const;
		void SetShininess(float shininess);
	};
}