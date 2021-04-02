#include "stdafx.h"
#include "DirLightComponent.h"

#include "Loco/GameObject.h"
#include "Loco/Renderer/Renderer.h"
#include "TransformComponent.h"

namespace Loco {

	DirLightComponent::DirLightComponent(GameObject* owenr, int updateOrder /*= 100*/)
		: LightComponent(owenr, updateOrder)
	{
		GetRenderer()->AddLightComp(this);
	}

	DirLightComponent::~DirLightComponent()
	{
		GetRenderer()->RemoveLightComp(this);
	}

	glm::vec3 DirLightComponent::GetDirection() const
	{
		return GetOwner()->GetTransform()->GetRotation();
	}

}