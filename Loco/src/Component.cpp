#include "stdafx.h"
#include "Component.h"

#include "GameObject.h"

namespace Loco {

	Component::Component(GameObject* owner, int updateOrder)
		: m_Owner(owner)
		, m_UpdateOrder(updateOrder)
	{
		m_Owner->AddComponent(this);
	}

	Component::~Component()
	{
		m_Owner->RemoveComponent(this);
	}

	void Component::OnUpdate(float deltaTime)
	{

	}
}
