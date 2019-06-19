#pragma once

#include <GL/glew.h>
#include <vector>
#include "Renderer.h"
#include <iostream>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type) 
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout(): m_stride(0) {}

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		std::cout << "vertex buffer layout adding GL_FLOAT element with count " << count << std::endl;
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
		std::cout << "stride is now " << m_stride << std::endl;
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		std::cout << "vertex buffer layout adding GL_UNSIGNED_INT element with count " << count << std::endl;
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
		std::cout << "stride is now " << m_stride << std::endl;
	}

	template<>
	void push<char>(unsigned int count)
	{
		std::cout << "vertex buffer layout adding GL_UNSIGNED_BYTE element with count " << count << std::endl;
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
		std::cout << "stride is now " << m_stride << std::endl;
	}

	inline const std::vector<VertexBufferElement> getElements() const& { return m_elements; }
	inline unsigned int getStride() const { return m_stride; }
};

