#include "stdafx.h"
#include <glad/glad.h>
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

	float TransformComponent::GetPosition(DIR dir)
	{
		switch (dir)
		{
		case Loco::DIR::X:
			return m_Position.x;
			break;
		case Loco::DIR::Y:
			return m_Position.y;
			break;
		case Loco::DIR::Z:
			return m_Position.z;
			break;
		}
	}

	float TransformComponent::GetRotation(DIR dir)
	{
		switch (dir)
		{
		case Loco::DIR::X:
			return m_Rotation.x;
			break;
		case Loco::DIR::Y:
			return m_Rotation.y;
			break;
		case Loco::DIR::Z:
			return m_Rotation.z;
			break;
		}
	}

	float TransformComponent::GetScale(DIR dir)
	{
		switch (dir)
		{
		case Loco::DIR::X:
			return m_Scale.x;
			break;
		case Loco::DIR::Y:
			return m_Scale.y;
			break;
		case Loco::DIR::Z:
			return m_Scale.z;
			break;
		}
	}

}