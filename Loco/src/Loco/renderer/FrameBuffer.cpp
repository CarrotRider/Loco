#include "stdafx.h"
#include "FrameBuffer.h"

#include "RenderBuffer.h"
#include "Loco/Texture.h"

namespace Loco {

	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_ID);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::BindTexture(const Texture& texture, unsigned attachment /*= GL_COLOR_ATTACHMENT0*/)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.GetID(), 0);
	}

	void FrameBuffer::BindRenderBuffer(const RenderBuffer& renderBuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER, renderBuffer.GetID());
	}

}