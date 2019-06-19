#include "IndexBuffer.h"
#include "Renderer.h"
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCall(glGenBuffers(1, &m_RendererID));
	std::cout << "generating buffer for index buffer on index " << m_RendererID << std::endl;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	std::cout << "binding index buffer on target GL_ELEMENT_ARRAY_BUFFER\n";
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	std::cout << "new data store created for index " << m_RendererID << " currently bound on target GL_ELEMENT_ARRAY_BUFFER with index buffer data\n";
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}