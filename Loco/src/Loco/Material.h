#pragma once
#include "Loco/Core.h"

namespace Loco {

	class Shader;

	enum class MaterialType
	{
		NONE, 
		SOILD_COLOR, PHONG_SOILD_COLOR, PHONE_TEXTURE
	};

//#define MATERIAL_TYPE(type) MaterialType GetType() override { return type; }

	class LOCO_API Material
	{
	public:
		Material(std::shared_ptr<Shader> shader)
			: m_Shader(shader) {}
		virtual ~Material() = default;
	
		virtual MaterialType GetType() = 0 { return MaterialType::NONE; }

		Shader* GetShader() const { return m_Shader.get(); }
	protected:
		std::shared_ptr<Shader> m_Shader;
	};
}


