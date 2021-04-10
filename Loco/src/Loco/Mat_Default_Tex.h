#pragma once
#include "Material.h"

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
	
	private:
		std::shared_ptr<Texture> m_DiffuseTexture;
		std::shared_ptr<Texture> m_SpecularTexture;
		std::shared_ptr<Texture> m_NormalTexture;
		float m_Shininess;
	};
}



