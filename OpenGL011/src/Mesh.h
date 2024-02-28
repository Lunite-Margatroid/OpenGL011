#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "Camera_K.h"
namespace LM
{	
	// 记得想办法释放单例
	class TextureTypeMap
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
	private:
		TextureTypeMap();

		static TextureTypeMap* GetInstance();

		std::vector<std::string> m_TexTypeName;
		std::vector<std::string> m_DiffTexUniformName;
		std::vector<std::string> m_SpecTexUniformName;
		std::vector<std::string> m_NormTexUniformName;
		std::vector<std::string> m_ParaTexUniformName;

	public:
		static TextureTypeMap* s_Instance;
		static const std::string& TextureType2Str(TextureType type);
		// index 最小为1 最大为8
		static const std::string& TextureType2UniformName(TextureType type, unsigned int index);
	};

	class Mesh
	{
	protected:
		const VertexArray* m_va;

		std::vector<Texture*> m_Textures;

		virtual void SetUniformTexture(Shader&) = 0;
	public:
		Mesh(VertexArray* va);
		virtual ~Mesh();
		virtual void Draw(Shader&);
		virtual void PushTexture(Texture*);
	};
}