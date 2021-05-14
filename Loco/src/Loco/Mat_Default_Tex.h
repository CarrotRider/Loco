#pragma once
#include "Material.h"
#include "glm/glm.hpp"

namespace Loco {

	class Texture;
	class Renderer;

	class LOCO_API Mat_Default_Tex :
		public Material
	{
	public:
		Mat_Default_Tex(std::shared_ptr<Shader> shader,
			std::shared_ptr<Texture> diffuseTex = nullptr,
			std::shared_ptr<Texture> specularTex = nullptr,
			std::shared_ptr<Texture> normalTex = nullptr,
			float shininess = 32.0f);
		Mat_Default_Tex(std::shared_ptr<Shader> shader,
			glm::vec3 diffuse = glm::vec3{ 0.5f, 0.5f, 0.5f },
			glm::vec3 specular = glm::vec3{ 1.0f, 1.0f, 1.0f },
			float shininess = 32.0f,
			glm::vec3 normal = glm::vec3{ 0.0f, 0.0f, 1.0f });
		virtual ~Mat_Default_Tex() = default;
	
		MaterialType GetType() override { return MaterialType::PHONE_TEXTURE; }
		
		// Getter & Setter
		void SetDiffuseTex(std::shared_ptr<Texture> texture) { m_DiffuseTexture = texture; }
		std::shared_ptr<Texture> GetDiffuseTex() const { return m_DiffuseTexture; }
		
		void SetSpecularTex(std::shared_ptr<Texture> texture) { m_SpecularTexture = texture; }
		std::shared_ptr<Texture> GetSpecularTex() const { return m_SpecularTexture; }
		
		void SetNormalTex(std::shared_ptr<Texture> texture) { m_NormalTexture = texture; }
		std::shared_ptr<Texture> GetNormalTex() const { return m_NormalTexture; }

		void SetShininess(float shininess) { m_Shininess = shininess; }
		float GetShininess() const { return m_Shininess; }

		void SetDiffuseColor(glm::vec3 diffuse) { m_DiffuseColor = diffuse; }
		glm::vec3 GetDiffuseColor() const { return m_DiffuseColor; }

		void SetSpecularColor(glm::vec3 specular) { m_SpecularColor = specular; }
		glm::vec3 GetSpecularColor() const { return m_SpecularColor; }

		void SetNormal(glm::vec3 normal) { m_Normal = normal; }
		glm::vec3 GetNormal() const { return m_Normal; }

		void SetDiffuseTexActive(bool bDiffuseTex) { m_bDiffuseTex = bDiffuseTex; }
		bool GetDiffuseTexActive() const { return m_bDiffuseTex; }

		void SetSpecularTexActive(bool bSpecularTex) { m_bSpecularTex = bSpecularTex; }
		bool GetSpecularTexActive() const { return m_bSpecularTex; }

		void SetNormalTexActive(bool bNormalTex) { m_bNormalTex = bNormalTex; }
		bool GetNormalTexActive() { return m_bNormalTex; }
	
	private:
		bool m_bDiffuseTex{ true };
		glm::vec3 m_DiffuseColor{ 0.5f, 0.5f, 0.5f };
		std::shared_ptr<Texture> m_DiffuseTexture{ nullptr };

		bool m_bSpecularTex{ true };
		glm::vec3 m_SpecularColor{ 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Texture> m_SpecularTexture{ nullptr };
		
		bool m_bNormalTex{ true };
		glm::vec3 m_Normal{ 0.0f, 0.0f, 1.0f };
		std::shared_ptr<Texture> m_NormalTexture{ nullptr };
		
		float m_Shininess{ 32.0f };
	};
}



