#pragma once
#include "Core.h"
namespace Loco {

	class LOCO_API RenderBuffer
	{
	public:
		RenderBuffer(unsigned type, int width, int height);
		~RenderBuffer();

		void Bind();
		void UnBind();

		unsigned GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
	};
}


