#pragma once
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void bind() const;
	void unbind() const;

private:
	unsigned int m_rendererID;
	unsigned int m_texColorBuffer;
	unsigned int m_rboDepthStencil;
};

