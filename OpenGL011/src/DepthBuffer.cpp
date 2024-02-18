#include "pch.h"
#include "DepthBuffer.h"
namespace LM
{
	DepthBuffer::DepthBuffer(int width, int height, unsigned char index)
	{
		m_width = width;
		m_height = height;
		m_texIndex = index;

		// 创建帧缓冲对象
		GLCall(glGenFramebuffers(1, &m_fboID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

		// 创建纹理对象
		// 作为颜色缓冲
		GLCall(glGenTextures(1, &m_texID));
		GLCall(glActiveTexture(GL_TEXTURE0 + m_texIndex));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));
		// 声明为深度附件
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
			m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

		// 设置环绕方式和插值方式
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


		// 绑定深度附件
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texID, 0));
		GLCall(glDrawBuffer(GL_NONE));
		GLCall(glReadBuffer(GL_NONE));
		// 检查完整性
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