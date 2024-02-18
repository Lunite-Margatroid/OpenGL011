#include "pch.h"
#include "DepthBuffer.h"
namespace LM
{
	DepthBuffer::DepthBuffer(int width, int height, unsigned char index)
	{
		m_width = width;
		m_height = height;
		m_texIndex = index;

		// ����֡�������
		GLCall(glGenFramebuffers(1, &m_fboID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

		// �����������
		// ��Ϊ��ɫ����
		GLCall(glGenTextures(1, &m_texID));
		GLCall(glActiveTexture(GL_TEXTURE0 + m_texIndex));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));
		// ����Ϊ��ȸ���
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
			m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

		// ���û��Ʒ�ʽ�Ͳ�ֵ��ʽ
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


		// ����ȸ���
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texID, 0));
		GLCall(glDrawBuffer(GL_NONE));
		GLCall(glReadBuffer(GL_NONE));
		// ���������
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
			__debugbreak();
		}
	}
	DepthBuffer::~DepthBuffer()
	{
	}
}