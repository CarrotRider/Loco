#include "stdafx.h"
#include "GameObject.h"
#include "Loco/Components/TransformComponent.h"

#include "Game.h"


namespace Loco {

	GameObject::GameObject(Game* game)
		: m_Game(game)
		, m_State(GameObjState::ACTIVE)
		, m_Transform(nullptr)
	{
		m_Game->AddGameObject(this);
		m_Transform = new TransformComponent(this);
		AddComponent(m_Transform);
	}

	GameObject::~GameObject()
	{
		m_Game->RemoveGameObject(this);
		while (!m_Components.empty())
		{
			delete m_Components.back();
		}
	}

	void GameObject::OnUpdate(float deltaTime)
	{
		if (m_State == GameObjState::ACTIVE)
		{
			UpdateComponents(deltaTime);
			UpdateGameObject(deltaTime);
		}
	}

	void GameObject::UpdateComponents(float deltaTime)
	{
		for (auto& comp : m_Components)
		{
			comp->OnUpdate(deltaTime);
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		int compOrder = component->GetUpdateOrder();
		auto iter = m_Components.begin();
		for (; iter != m_Components.end(); ++iter)
		{
			if (compOrder < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}
		m_Components.insert(iter, component);
	}

	void GameObject::RemoveComponent(Component* component)
	{
		auto iter = std::find(m_Components.begin(), m_Components.end(), component);
		if (iter != m_Components.end())
		{
			m_Components.erase(iter);
			delete component;
		}
	}
}
