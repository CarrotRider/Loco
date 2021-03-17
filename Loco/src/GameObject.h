#pragma once

#include "Component.h"
#include "TransformComponent.h"

namespace Loco {

	class Game;

	enum class GameObjState
	{
		ACTIVE, PAUSED, DEAD
	};

	class GameObject
	{
	public:
		GameObject(Game* game);
		virtual ~GameObject();

		void OnUpdate(float deltaTime);
		void UpdateComponents(float deltaTime);
		virtual void UpdateGameObject(float deltaTime);

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);

		Game* GetGame() { return m_Game; }
		GameObjState GetState() const { return m_State; }
		void SetState(GameObjState state) { m_State = state; }
	private:
		Game* m_Game;
		GameObjState m_State;
		TransformComponent* m_Transform;
		std::vector<Component*> m_Components;
	};

}


