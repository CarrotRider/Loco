#pragma once
#include "Component.h"

namespace Loco {

	class Renderer;
	class GameObject;
	class Shader;

	class RenderableComponent :
		public Component
	{
	public:
		RenderableComponent(GameObject* owner, int updateOrder = 100);
		virtual ~RenderableComponent() {};

		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnDraw(Shader* shader) = 0;

		Renderer* GetRenderer();

		void SetVisible(bool visible) { m_Visible = visible; }
		bool GetVisible() const { return m_Visible; }
	protected:
		bool m_Visible;
	};

}


