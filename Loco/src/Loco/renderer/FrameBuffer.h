#pragma once
#include <glad/glad.h>
#include "Loco/Core.h"

namespace Loco {

	class RenderBuffer;
	class Texture;

	class LOCO_API FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void Bind();
		void UnBind();

		void BindTexture(const Texture& texture, 
			unsigned attachment = GL_COLOR_ATTACHMENT0,
			unsigned textarget = GL_TEXTURE_2D);
		void BindRenderBuffer(const RenderBuffer& renderBuffer);

		unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
	};

}


