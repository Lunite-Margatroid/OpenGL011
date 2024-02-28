#include "pch.h"
#include "Mesh3D.h"

namespace LM
{
	Mesh3D::Mesh3D(VertexArray* va, float shininess)
		:Mesh(va),m_shininiess(shininess)
	{
	}
	Mesh3D::Mesh3D(float shininess)
		:Mesh(nullptr), m_shininiess(shininess)
	{
	}
	Mesh3D::~Mesh3D()
	{
	}
	void Mesh3D::SetUniformTexture(Shader& shader)
	{
		unsigned char count[4];
		memset(count, 0, 4);
		for (auto i = m_Textures.begin(); i != m_Textures.end(); i++)
		{
			Texture* tex = (*i);
			TextureType type = tex->GetTextureType();
			tex->Bind();
			shader.SetUniformTexture(TextureTypeMap::TextureType2UniformName(type, ++count[type - 1]), tex->GetIndex());
		}
		shader.SetUniform1f("u_material.shininess", m_shininiess);
	}
	void Mesh3D::Init(VertexArray* va)
	{
		Mesh::m_va = va;
	}
	float Mesh3D::GetShininess() const
	{
		return m_shininiess;
	}
	void Mesh3D::SetShininess(float shininess)
	{
		m_shininiess = shininess;
	}
}