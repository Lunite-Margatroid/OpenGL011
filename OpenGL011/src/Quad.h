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
		bool m_bCenter;	// quad��(0,0)�Ƿ������� Ĭ��Ϊfalse (0,0)�����½�

	public:
		Quad(float width,float height, bool bCenter = false);
		Quad(const Texture& tex,bool bCenter = false);
		virtual ~Quad();

		void Draw();

		bool IfCenter() const;
		bool IfTextured() const;
	};


}