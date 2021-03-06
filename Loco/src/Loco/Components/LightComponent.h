#pragma once

#include "Loco/Core.h"

#include "Loco/Component.h"

#include <glm/glm.hpp>

namespace Loco {

	class Renderer;

	class LOCO_API LightComponent :
		public Component
	{
	public:
		LightComponent(GameObject* owner, int updateOrder = 100);
		virtual ~LightComponent() = default;

		void OnUpdate(float deltaTime) override {}

		glm::vec3 GetColor() const { return m_Color; }
		void SetColor(glm::vec3 color) { m_Color = color; }

		Renderer* GetRenderer();

		glm::vec3 GetPosition() const;
	protected:
		glm::vec3 m_Color;
	};

}



