#pragma once
#include "Loco/Core.h"
#include "Loco/Component.h"

namespace Loco {

	class Renderer;
	class GameObject;
	class Shader;

	class LOCO_API RenderableComponent :
		public Component
	{
	public:
		RenderableComponent(GameObject* owner, int updateOrder = 100);
		virtual ~RenderableComponent() {};

		virtual void OnUpdate(float deltaTime) = 0;
		virtual void Draw() = 0;

		Renderer* GetRenderer();

		void SetVisible(bool visible) { m_Visible = visible; }
		bool GetVisible() const { return m_Visible; }
	protected:
		bool m_Visible;
	};

}


