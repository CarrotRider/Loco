#pragma once
#include "stdafx.h"
#include "Core.h"
#include "Component.h"
#include <glm/glm.hpp>

namespace Loco {

	enum class DIR { X, Y, Z};
	
	class LOCO_API TransformComponent :
		public Component
	{
	public:
		TransformComponent(GameObject* owner, int updateOrder = 100);
		virtual ~TransformComponent();

		virtual void OnUpdate(float deltaTime) override;

		// Getter & Setter
		void SetPosition(const glm::vec3& position) { m_Position = position; }
		glm::vec3 GetPosition() const { return m_Position; }
		float GetPosition(DIR dir);
		
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		glm::vec3 GetRotation() const { return m_Rotation; }
		float GetRotation(DIR dir);

		void SetScale(const glm::vec3& scale) { m_Scale = scale; }
		glm::vec3 GetScale() const { return m_Scale; }
		float GetScale(DIR dir);
		

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};

}


