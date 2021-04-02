#pragma once

#include "Loco/Core.h"

#include "LightComponent.h"

#include <glm/glm.hpp>

namespace Loco {

	class Renderer;
	
	class LOCO_API DirLightComponent :
		public LightComponent
	{
	public:
		DirLightComponent(GameObject* owenr, int updateOrder = 100);
		virtual ~DirLightComponent();

		void OnUpdate(float deltaTime) override {}

		glm::vec3 GetDirection() const;
	};
}


