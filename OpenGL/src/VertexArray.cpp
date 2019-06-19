#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();

	std::cout << "binding the vertex array to set up glEnableVertexAttribArray, then binding the vertex buffer\n";
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		std::cout << "calling glEnableVertexAttribArray on vertex array element " << i << std::endl;
		GLCall(glEnableVertexAttribArray(i));
		std::cout << "calling glVertexAttribPointer on vertex array element " << i << " and passing count " << element.count << ", type " << element.type << ", normalized " << element.normalized << ", with stride " << layout.getStride() << std::endl;
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		std::cout << "offset updated to " << offset << std::endl;

		/* as i understand it, this is about remembering the layout of the vertex array that its going to be getting. */
	}
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
	std::cout << "breaking the existing vertex array object binding\n";
}
