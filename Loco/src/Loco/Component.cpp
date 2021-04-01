#include "stdafx.h"
#include "Component.h"
#include "Game.h"
#include "GameObject.h"

namespace Loco {

	Component::Component(GameObject* owner, int updateOrder)
		: m_Owner(owner)
		, m_UpdateOrder(updateOrder)
	{
		//m_Owner->AddComponent(this);
	}

	Component::~Component()
	{
		m_Owner->RemoveComponent(this);
	}

	GameObject* Component::GetOwner() const
	{
		return m_Owner;
	}

	Game* Component::GetGame() const
	{
		return m_Owner->GetGame();
	}

	int Component::GetUpdateOrder() const
	{
		return m_UpdateOrder;
	}

}
