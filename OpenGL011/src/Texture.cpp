#include "pch.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <wchar.h>
#include <codecvt>
namespace LM
{

	bool Texture::LoadTexture(unsigned int* texture, const std::string& path, unsigned char index, int texColorMode, int resColorMode, bool bGenerateMipmap)
	{
		int nChannals;
		unsigned char* img_data;
		img_data = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &nChannals, 0);

		if (img_data == 0)
		{
			std::cout << "Fail to load img!----" << path << std::endl;
			return false;
		}
		GLCall(glGenTextures(1, texture));
		GLCall(glActiveTexture(GL_TEXTURE0 + index));
		GLCall(glBindTexture(GL_TEXTURE_2D, *texture)); // 绑定纹理


		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texColorMode, m_nWidth, m_nHeight, 0, resColorMode, GL_UNSIGNED_BYTE, img_data));
		// param1 纹理Target
		// param2 多级渐远级别 0为基本级别
		// param3 纹理格式
		// param4&5 宽度和高度x&y
		// param6 历史遗留 恒为0
		// param7 源数据格式
		// param8 源数据类型
		// param9 源数据

		if (bGenerateMipmap)
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// 自动生成多级渐远级别纹理
		stbi_image_free(img_data);						// 释放图像资源
		return true;
	}

	Texture::Texture(const std::string& imgPath, unsigned char index, int texColorMode, int imgColorMode, bool bGenerateMipmap, TextureType type)
		:m_type(type)
	{
		this->LoadTexture(&m_uTextureID, imgPath, index, texColorMode, imgColorMode, true);
		m_ubTextureIndex = index;
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));		// 设置环绕方式

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	// 设置插值方式
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_uTextureID));
	}

	void Texture::Bind()
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + m_ubTextureIndex));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_uTextureID));
	}

	unsigned char Texture::GetIndex() const
	{
		return m_ubTextureIndex;
	}
	unsigned int Texture::GetTexID() const
	{
		return m_uTextureID;
	}
	
	const std::string& Texture::GetTexType()
	{
		// TODO: 在此处插入 return 语句
		return m_strType;
	}
	const aiString& Texture::GetTexPath()
	{
		// TODO: 在此处插入 return 语句
		return m_aistrPath;
	}
	int Texture::GetHeight() const
	{
		return m_nHeight;
	}

	int Texture::GetWidth() const
	{
		return m_nWidth;
	}
	void Texture::SetTextureWrapS(GLenum texWrap)
	{
		Bind();
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrap));
	}
	void Texture::SetTextureWrapT(GLenum texWrap)
	{
		Bind();
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texWrap));
	}
	TextureType Texture::GetTextureType() const
	{
		return m_type;
	}
	void Texture::SetTextureType(TextureType type)
	{
		m_type = type;
	}
}