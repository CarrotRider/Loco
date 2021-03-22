#pragma once

namespace Loco {

	class Game;
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* owner, int updateOrder=100);
		virtual ~Component();

		virtual void OnUpdate(float deltaTime) = 0;

		GameObject* GetOwner();
		Game* GetGame();
		int GetUpdateOrder() const;
	protected:
		GameObject* m_Owner;
		int m_UpdateOrder;
	};

}


