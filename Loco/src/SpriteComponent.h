#pragma once
#include "Component.h"

#include "Texture.h"
#include "Shader.h"

namespace Loco {

	class SpriteComponent :
		public Component
	{
	public:
		SpriteComponent(GameObject* owner, int drawOrder = 100);
		virtual ~SpriteComponent();

		virtual void Draw(Shader* shader);
		virtual void SetTexture(Texture* texture);

		void SetVisible(bool visible) { m_Visible = visible; }
		bool GetVisible() const { return m_Visible; }

		int GetDrawOrder() const { return m_DrawOrder; }
		int GetTexWidth() const { return m_TexWidth; }
		int GetTexHeight() const { return m_TexHeight; }
	protected:
		Texture* m_Texture;
		int m_DrawOrder;
		int m_TexWidth;
		int m_TexHeight;
		bool m_Visible;
	};

}


