#include "stdafx.h"
#include "RenderBuffer.h"

#include <glad/glad.h>

namespace Loco {

	RenderBuffer::RenderBuffer(unsigned type, int width, int height)
	{
		glGenRenderbuffers(1, &m_ID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
		glRenderbufferStorage(GL_RENDERBUFFER, type, width, height);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_ID);
	}

	void RenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
	}

	void RenderBuffer::UnBind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

}