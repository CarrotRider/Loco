#pragma once

namespace Loco {

	class GameObject;

	class Component
	{
	public:
		Component(GameObject* owner, int updateOrder=100);
		virtual ~Component();

		virtual void OnUpdate(float deltaTime);

		GameObject* GetOwner() { return m_Owner; }
		int GetUpdateOrder() const { return m_UpdateOrder; }
	private:
		GameObject* m_Owner;
		int m_UpdateOrder;
	};

}


