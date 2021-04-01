#pragma once

#include "Core.h"

namespace Loco {

	class Game;
	class GameObject;

	class LOCO_API Component
	{
	public:
		Component(GameObject* owner, int updateOrder=100);
		virtual ~Component();

		virtual void OnUpdate(float deltaTime) = 0;

		GameObject* GetOwner() const;
		Game* GetGame() const;

		int GetUpdateOrder() const;
		bool GetActive() const { return m_Active; }
		void SetActive(bool active) { m_Active = active; }
	protected:
		GameObject* m_Owner;
		int m_UpdateOrder;
		bool m_Active;
	};

}


