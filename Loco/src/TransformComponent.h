#pragma once
#include "Component.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Loco {
	
	class TransformComponent :
		public Component
	{
	public:
		TransformComponent(GameObject* owner, int updateOrder = 100);
		virtual ~TransformComponent() override;

		virtual void OnUpdate(float deltaTime) override;

		// Getter & Setter
		glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; }
		glm::vec3 GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		glm::vec3 GetScale() const { return m_Scale; }
		void SetScale(const glm::vec3& scale) { m_Scale = scale; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};

}


