#include "stdafx.h"
#include "TransformComponent.h"
#include "LightComponent.h"

#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

namespace Loco {

	LightComponent::LightComponent(GameObject* owenr, int updateOrder /*= 100*/)
		: Component(owenr, updateOrder)
		, m_Color(glm::vec3(1.0f, 1.0f, 1.0f))
	{
		GetRenderer()->AddLightComp(this);
	}

	LightComponent::~LightComponent()
	{
		GetRenderer()->RemoveLightComp(this);
	}

	Renderer* LightComponent::GetRenderer()
	{
		return GetGame()->GetRenderer();
	}

	glm::vec3 LightComponent::GetPosition() const
	{
		return GetOwner()->GetTransform()->GetPosition();
	}

	glm::vec3 LightComponent::GetDirection() const
	{
		return GetOwner()->GetTransform()->GetRotation();
	}

}