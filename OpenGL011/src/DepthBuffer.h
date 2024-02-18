#pragma once
#include "FrameBuffer.h"

namespace LM
{
	class DepthBuffer : public FrameBuffer
	{
	public:
		/// <summary>
		/// 构造函数
		/// </summary>
		/// <param name="width"> 宽 </param>
		/// <param name="height"> 高 </param>
		/// <param name="index"> 纹理slot的id 默认为0 </param>
		DepthBuffer(int width = 1024, int height = 1024, unsigned char index = 0);

		~DepthBuffer();
	};
}