#pragma once

#include "Core.h"

namespace Loco {

	class Game;
	class Component;
	class TransformComponent;

	enum class GameObjState
	{
		ACTIVE, PAUSED, DEAD
	};

	class LOCO_API GameObject
	{
	public:
		GameObject(Game* game);
		virtual ~GameObject();

		void OnUpdate(float deltaTime);
		void UpdateComponents(float deltaTime);
		virtual void UpdateGameObject(float deltaTime) {};

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		
		Game* GetGame() { return m_Game; }
		TransformComponent* GetTransform() { return m_Transform; }

		void SetState(GameObjState state) { m_State = state; }
		GameObjState GetState() const { return m_State; }
	private:
		Game* m_Game;
		GameObjState m_State;
		TransformComponent* m_Transform;
		std::vector<Component*> m_Components;
	};

}


