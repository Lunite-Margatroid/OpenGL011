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
		GLCall(glBindTexture(GL_TEXTURE_2D, *texture)); // ������


		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texColorMode, m_nWidth, m_nHeight, 0, resColorMode, GL_UNSIGNED_BYTE, img_data));
		// param1 ����Target
		// param2 �༶��Զ���� 0Ϊ��������
		// param3 �����ʽ
		// param4&5 ��Ⱥ͸߶�x&y
		// param6 ��ʷ���� ��Ϊ0
		// param7 Դ���ݸ�ʽ
		// param8 Դ��������
		// param9 Դ����

		if (bGenerateMipmap)
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// �Զ����ɶ༶��Զ��������
		stbi_image_free(img_data);						// �ͷ�ͼ����Դ
		return true;
	}

	Texture::Texture(const std::string& imgPath, unsigned char index, int texColorMode, int imgColorMode, bool bGenerateMipmap, TextureType type)
		:m_type(type)
	{
		this->LoadTexture(&m_uTextureID, imgPath, index, texColorMode, imgColorMode, true);
		m_ubTextureIndex = index;
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));		// ���û��Ʒ�ʽ

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	// ���ò�ֵ��ʽ
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
	void Texture::InitFromModelFile(const char* filename, const std::string& directory, const std::string& type)
	{
		/*
		����ͼƬ��·����������
		ģ���ļ���¼���������ݵ�·���������utf-8��ʾ
		fopen��֧��utf-8
		�����utf-8תΪ���ַ� ����wfopen���ļ�

		Ȼ������ģ���ļ����ǲ�֧������·�� �����
	    */
		// ---��ʼ��---
		m_aistrPath = filename;
		m_strType = type;
		//------------
		int width, height, nChannals;
		unsigned char* img_data = 0;

		GLCall(glGenTextures(1, &m_uTextureID));
		// �������ͼƬ·��
		std::stringstream ss;
		ss << directory << "/" << filename;
		std::string path = ss.str();

		// utf-8תΪ���ַ�
		std::wstring wstr;
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		wstr = wcv.from_bytes(path);
		FILE* f;
		_wfopen_s(&f, wstr.c_str(), L"rb");	// ���ַ����open file
		if (f)
		{
			img_data = stbi_load_from_file(f, &width, &height, &nChannals, 0);
			fclose(f);
		}
		if (img_data == 0)
		{
			std::cout << "Fail to load img!" << std::endl;
			std::wcout << wstr << std::endl;
		}
		else
		{
			GLenum format;
			if (nChannals == 1)
				format = GL_RED;
			else if (nChannals == 3)
				format = GL_RGB;
			else if (nChannals == 4)
				format = GL_RGBA;

			GLCall(glBindTexture(GL_TEXTURE_2D, m_uTextureID)); // ������
			// param1 ����Target
			// param2 �༶��Զ���� 0Ϊ��������
			// param3 �����ʽ
			// param4&5 ��Ⱥ͸߶�x&y
			// param6 ��ʷ���� ��Ϊ0
			// param7 Դ���ݸ�ʽ
			// param8 Դ��������
			// param9 Դ����
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
				0, format, GL_UNSIGNED_BYTE, img_data));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// �Զ����ɶ༶��Զ��������
			stbi_image_free(img_data);						// �ͷ�ͼ����Դ
		}
	}
	const std::string& Texture::GetTexType()
	{
		// TODO: �ڴ˴����� return ���
		return m_strType;
	}
	const aiString& Texture::GetTexPath()
	{
		// TODO: �ڴ˴����� return ���
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