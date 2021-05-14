#include "stdafx.h"
#include "Mat_Default_Tex.h"

namespace Loco {

	Mat_Default_Tex::Mat_Default_Tex(std::shared_ptr<Shader> shader, 
		std::shared_ptr<Texture> diffuseTex /*= nullptr*/, 
		std::shared_ptr<Texture> specularTex /*= nullptr*/, 
		std::shared_ptr<Texture> normalTex /*= nullptr*/, 
		float shininess /*= 32.0f*/)
		: Material(shader)
		, m_DiffuseTexture(diffuseTex)
		, m_SpecularTexture(specularTex)
		, m_NormalTexture(normalTex)
		, m_Shininess(shininess)
	{
		if (!m_DiffuseTexture.get())
			SetDiffuseTexActive(false);
		if (!m_SpecularTexture.get())
			SetSpecularTexActive(false);
		if (!m_NormalTexture.get())
			SetNormalTexActive(false);
	}

	Mat_Default_Tex::Mat_Default_Tex(std::shared_ptr<Shader> shader, 
		glm::vec3 diffuse /*= glm::vec3{ 0.5f, 0.5f, 0.5f }*/, 
		glm::vec3 specular /*= glm::vec3{ 1.0f, 1.0f, 1.0f }*/, 
		float shininess /*= 32.0f*/,
		glm::vec3 normal /*= glm::vec3{ 0.0f, 0.0f, 1.0f }*/)
		: Material(shader)
		, m_bDiffuseTex(false)
		, m_DiffuseColor(diffuse)
		, m_bSpecularTex(false)
		, m_SpecularColor(specular)
		, m_bNormalTex(false)
		, m_Normal(normal)
		,m_Shininess(shininess)
	{
	}
}