#include "pch.h"
#include "Quad.h"

LM::Quad::Quad(float width, float height, bool bCenter):m_bTextured(false), m_bCenter(bCenter)
{
	m_pIndice = nullptr;
	m_pVertice = new float[8];
	float offsetX = 0.0f, offsetY = 0.0f;
	if (m_bCenter)
	{
		offsetX = -width / 2.0f;
		offsetY = -height / 2.0f;
	}

	m_pVertice[0] = 0.0f + offsetX;
	m_pVertice[1] = 0.0f + offsetY;

	m_pVertice[2] = width + offsetX;
	m_pVertice[3] = 0.0f + offsetY;

	m_pVertice[4] = width + offsetX;
	m_pVertice[5] = height + offsetY;

	m_pVertice[6] = 0.0f + offsetX;
	m_pVertice[7] = height + offsetY;

	VertexBuffer::Init(8 * sizeof(float), m_pVertice);

	VertexArray::PushAttrib<float>(2);
	VertexArray::ApplyLayout();
}

LM::Quad::Quad(const Texture& tex, bool bCenter): m_bTextured(true), m_bCenter(bCenter)
{
	m_pIndice = nullptr;
	m_pVertice = new float[16];

	int height = tex.GetHeight();
	int width = tex.GetWidth();
	float fHeight = 1.0f;
	float fWidth = (float)width / (float)height;
	float offsetX = 0.0f, offsetY = 0.0f;
	if (m_bCenter)
	{
		offsetX = -fWidth / 2.0f;
		offsetY = -fHeight / 2.0f;
	}
	// Í¼Æ¬µÄ×óÉÏ½ÇÊÇ(0,0)
	float vertice[] =
	{
		0.0f + offsetX,		0.0f + offsetY,			0.0f, 1.0f,
		fWidth + offsetX,	0.0f + offsetY,			1.0f, 1.0f,
		fWidth + offsetX,	fHeight + offsetY,		1.0f, 0.0f,
		0.0f + offsetX,		fHeight + offsetY,		0.0f, 0.0f
	};
	memcpy(m_pVertice, vertice, 16 * sizeof(float));
	VertexBuffer::Init(16 * sizeof(float), m_pVertice);
	VertexArray::PushAttrib<float>(2);
	VertexArray::PushAttrib<float>(2);
	VertexArray::ApplyLayout();
}

LM::Quad::~Quad()
{
	if (m_pIndice)
		delete[] m_pIndice;

	if (m_pVertice)
		delete[] m_pVertice;
}

void LM::Quad::Draw()
{
	VertexArray::Bind();

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

bool LM::Quad::IfCenter() const
{
	return m_bCenter;
}

bool LM::Quad::IfTextured() const
{
	return m_bTextured;
}
