#include "trpch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
{
	glBindVertexArray(m_RendererID);
	vertexBuffer->bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_vertexBuffer = vertexBuffer;
}

void VertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->bind();
	m_indexBuffer = indexBuffer;
}
