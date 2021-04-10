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
	}

}