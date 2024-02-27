#include "pch.h"
#include "VertexArray.h"

LM::VertexArray::VertexArray()
	:m_stride(0)
{
	GLCall(glGenVertexArrays(1, &m_id));
	Bind();
}


LM::VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void LM::VertexArray::ApplyLayout()
{
	int i = 0;
	unsigned int offset = 0;
	Bind();
	for (auto& attr : m_attribLayout)
	{
		glVertexAttribPointer(i, attr.count , attr.type, attr.bNormalize, \
			m_stride, (void*)offset);
		glEnableVertexAttribArray(i);

		/*GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
		glEnableVertexAttribArray(0);*/

		offset += AttribLayout::GetSizeOfElem(attr.type) * attr.count;

		i++;
	}
}

unsigned int LM::VertexArray::GetID() const
{
	return m_id;
}

void LM::VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_id));
}

void LM::VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
