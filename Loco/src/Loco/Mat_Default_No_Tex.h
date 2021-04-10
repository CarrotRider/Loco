#pragma once
#include "Material.h"

#include <glm/glm.hpp>

namespace Loco {

	class LOCO_API Mat_Default_No_Tex :
		public Material
	{
	public:
		Mat_Default_No_Tex(std::shared_ptr<Shader> shader,
			const glm::vec3& diffuseColor = glm::vec3(0.5f, 0.5f, 0.5f),
			const glm::vec3& specularColor = glm::vec3(0.9f, 0.9f, 0.9f),
			float shininess = 32.0f);
		virtual ~Mat_Default_No_Tex() = default;

		MaterialType GetType() override { return MaterialType::PHONG_SOILD_COLOR; }

		// Getter & Setter
		void SetDiffuseColor(const glm::vec3& color) { m_DiffuseColor = color; }
		glm::vec3 GetDiffuseColor() const { return m_DiffuseColor; }

		void SetSpecularColor(const glm::vec3& color) { m_SpecularColor = color; }
		glm::vec3 GetSpecularColor() const { return m_SpecularColor; }

		void SetShininess(float shininess) { m_Shininess = shininess; }
		float GetShininess() const { return m_Shininess; }

	private:
		glm::vec3 m_DiffuseColor;
		glm::vec3 m_SpecularColor;
		float m_Shininess;
	};
}


