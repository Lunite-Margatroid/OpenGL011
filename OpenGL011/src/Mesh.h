#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "Camera_K.h"
namespace LM
{	
	// �ǵ���취�ͷŵ���
	class TextureTypeMap
	{
		/*
		enum TextureType : uint8_t
		{
			texture_uknown,
			texture_diffuse,	// ����������
			texture_specular,	// ���淴������
			texture_normal,		// ��������
			texture_parallax	// �Ӳ���ͼ
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
		// index ��СΪ1 ���Ϊ8
		static const char* TextureType2UniformName(TextureType type, unsigned int index);
	};

	class Mesh
	{
	protected:
		const VertexBuffer* m_vb;
		const ElementBuffer* m_eb;
		const VertexArray* m_va;

		float m_RotationRad;

		std::vector<Texture*> m_Textures;

		virtual void SetUniform(Shader&, Camera&, const glm::mat4* parentModelTrans = NULL) = 0;
	public:
		Mesh(VertexBuffer* vb, ElementBuffer* eb, VertexArray* va, float rotationRad = 0.0f);
		virtual ~Mesh();
		virtual void Draw(Shader&);
		virtual void PushTexture(Texture*);
	};
}