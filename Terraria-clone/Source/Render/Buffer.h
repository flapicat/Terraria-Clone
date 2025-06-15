#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();
	void bind();
	void unbind();
private:
	unsigned int m_RendererID;
};

class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();
	void bind();
	void unbind();

	unsigned int GetCount() { return m_Count; }
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};

