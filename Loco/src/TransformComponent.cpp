#include "stdafx.h"
#include "TransformComponent.h"

namespace Loco {

	TransformComponent::TransformComponent(GameObject* owner, 
		int updateOrder /*= 100*/)
		: Component(owner, updateOrder)
		, m_Position(glm::vec3(0.0f, 0.0f, 0.0f))
		, m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f))
		, m_Scale(glm::vec3(1.0f, 1.0f, 1.0f))
	{

	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::OnUpdate(float deltaTime)
	{
		
	}

}