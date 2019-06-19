#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	std::cout << "Generated 1 buffer object on vertex buffer " << m_RendererID << std::endl;
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	std::cout << "Vertex buffer " << m_RendererID << " bound to GL_ARRAY_BUFFER target\n";
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	std::cout << "New data store created for buffer object " << m_RendererID << " currently bound on target GL_ARRAY_BUFFER\n";
	std::cout << "Usage is GL_STATIC_DRAW: the data store contents will be modified once by the application and used many times as the source for GL drawing and image specification commands\n";
	std::cout << "Data store is " << size << " bytes\n";
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}