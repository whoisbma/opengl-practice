#include "FrameBuffer.h"
#include "Renderer.h"
#include <iostream>

FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &m_rendererID));

	GLCall(glGenTextures(1, &m_texColorBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texColorBuffer));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColorBuffer, 0));

	GLCall(glGenRenderbuffers(1, &m_rboDepthStencil));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepthStencil));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 640, 480));

	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboDepthStencil));

}


FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteRenderbuffers(1, &m_rboDepthStencil));
	GLCall(glDeleteFramebuffers(1, &m_rendererID));
}

void FrameBuffer::bind() const
{
	//GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID));
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "framebuffer bind error\n";
	}
}

void FrameBuffer::unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}