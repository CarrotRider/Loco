#pragma once

#include "Core.h"
#include "Component.h"

#include <glm/glm.hpp>

namespace Loco {

	class Renderer;

	class LOCO_API LightComponent :
		public Component
	{
	public:
		LightComponent(GameObject* owenr, int updateOrder = 100);
		virtual ~LightComponent();

		virtual void OnUpdate(float deltaTime) override {}

		glm::vec3 GetColor() const { return m_Color; }
		void SetColor(glm::vec3 color) { m_Color = color; }

		Renderer* GetRenderer();

		glm::vec3 GetPosition() const;
		glm::vec3 GetDirection() const;
	protected:
		glm::vec3 m_Color;
	};
}


