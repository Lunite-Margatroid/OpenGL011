#pragma once
#include "FrameBuffer.h"

namespace LM
{
	class DepthBuffer : public FrameBuffer
	{
	public:
		/// <summary>
		/// ���캯��
		/// </summary>
		/// <param name="width"> �� </param>
		/// <param name="height"> �� </param>
		/// <param name="index"> ����slot��id Ĭ��Ϊ0 </param>
		DepthBuffer(int width = 1024, int height = 1024, unsigned char index = 0);

		~DepthBuffer();
	};
}