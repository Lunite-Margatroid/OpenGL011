#include "pch.h"
#include "Mesh.h"
namespace LM
{
	TextureTypeMap* TextureTypeMap::s_Instance = nullptr;

	TextureTypeMap::TextureTypeMap()
	{
		/*
		enum TextureType : uint8_t
		{
			texture_uknown,
			texture_diffuse,	// 漫反射纹理
			texture_specular,	// 镜面反射纹理
			texture_normal,		// 法线纹理
			texture_parallax	// 视差贴图
		};
		*/

		m_TexTypeName.emplace_back("texture_uknown");
		m_TexTypeName.emplace_back("texture_diffuse");
		m_TexTypeName.emplace_back("texture_specular");
		m_TexTypeName.emplace_back("texture_normal");
		m_TexTypeName.emplace_back("texture_parallax");

		std::string materialName("u_material.");
		for (int i = 0; i < 8; i++)
		{
			m_DiffTexUniformName.emplace_back(materialName + m_TexTypeName[1] + char('1' + i));
			m_SpecTexUniformName.emplace_back(materialName + m_TexTypeName[2] + char('1' + i));
			m_NormTexUniformName.emplace_back(materialName + m_TexTypeName[3] + char('1' + i));
			m_ParaTexUniformName.emplace_back(materialName + m_TexTypeName[4] + char('1' + i));
		}
	}

	const std::string& TextureTypeMap::TextureType2Str(TextureType type)
	{
		return GetInstance()->m_TexTypeName[type];
	}
	const std::string& TextureTypeMap::TextureType2UniformName(TextureType type, unsigned int index)
	{
		TextureTypeMap* instance = GetInstance();
		if (index < 1 || index > 8)
		{
			std::cout << "texture count out of range.\n";
			return nullptr;
		}
		switch (type)
		{
		case texture_uknown: return nullptr;
		case texture_diffuse: return instance->m_DiffTexUniformName[index - 1];
		case texture_specular: return instance->m_SpecTexUniformName[index - 1];
		case texture_normal: return instance->m_NormTexUniformName[index - 1];
		case texture_parallax: return instance->m_ParaTexUniformName[index - 1];
		default:return nullptr;
		}
		return nullptr;
	}


	TextureTypeMap* TextureTypeMap::GetInstance()
	{
		if (s_Instance)
			return s_Instance;

		s_Instance = new TextureTypeMap();
	}




	Mesh::Mesh(VertexArray* va)
		: m_va(va)
	{
	}
	Mesh::~Mesh()
	{
	}
	void Mesh::Draw(Shader& shader)
	{
		shader.Bind();
		SetUniformTexture(shader);
		m_va->Draw();
	}
	void Mesh::PushTexture(Texture* texture)
	{
		m_Textures.push_back(texture);
	}


}