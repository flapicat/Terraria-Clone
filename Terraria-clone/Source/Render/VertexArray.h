#pragma once
#include <memory>
#include "Buffer.h"


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();
	void setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
	void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

	std::shared_ptr<VertexBuffer> getVertexBuffer() { return m_vertexBuffer; };
	std::shared_ptr<IndexBuffer> getIndexBuffer() { return m_indexBuffer; };
private:
	unsigned int m_RendererID;
	std::shared_ptr<VertexBuffer> m_vertexBuffer;
	std::shared_ptr<IndexBuffer> m_indexBuffer;
};

