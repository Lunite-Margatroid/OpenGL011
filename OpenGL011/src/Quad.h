#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
namespace LM
{
	class Quad:public VertexBuffer, VertexArray
	{
	private:
		unsigned int* m_pIndice;
		float* m_pVertice;
		bool m_bTextured;
		bool m_bCenter;	// quad的(0,0)是否在中心 默认为false (0,0)在左下角

	public:
		Quad(float width,float height, bool bCenter = false);
		Quad(const Texture& tex,bool bCenter = false);
		virtual ~Quad();

		void Draw();

		bool IfCenter() const;
		bool IfTextured() const;
	};


}