#include "stdafx.h"
#include "Mat_Default_No_Tex.h"

namespace Loco {

	Mat_Default_No_Tex::Mat_Default_No_Tex(
		std::shared_ptr<Shader> shader, 
		const glm::vec3& diffuseColor /*= glm::vec3(0.5f, 0.5f, 0.5f)*/, 
		const glm::vec3& specularColor /*= glm::vec3(0.9f, 0.9f, 0.9f)*/, 
		float shininess /*= 32.0f*/)
		: Material(shader)
		, m_DiffuseColor(diffuseColor)
		, m_SpecularColor(specularColor)
		, m_Shininess(shininess)
	{

	}

}