#include "stdafx.h"
#include "LightComponent.h"

#include "Loco/Game.h"
#include "Loco/GameObject.h"
#include "Loco/Renderer/Renderer.h"
#include "TransformComponent.h"

namespace Loco {

	LightComponent::LightComponent(GameObject* owner, int updateOrder /*= 100*/)
		: Component(owner, updateOrder)
		, m_Color(glm::vec3(1.0f, 1.0f, 1.0f))
	{
	}

	Loco::Renderer* LightComponent::GetRenderer()
	{
		return GetGame()->GetRenderer();
	}

	glm::vec3 LightComponent::GetPosition() const
	{
		return GetOwner()->GetTransform()->GetPosition();
	}

}