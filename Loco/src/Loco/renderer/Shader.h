#pragma once

#include "Core.h"

#include <glm/glm.hpp>

namespace Loco {
	
	class LOCO_API Shader
	{
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		virtual ~Shader();

		void Bind() const;
		void UnBind() const;
		
		unsigned int ID() const { return m_ID; }

		void SetUniform(const std::string& name, bool value) const;
		void SetUniform(const std::string& name, int value) const;
		void SetUniform(const std::string& name, unsigned value) const;
		void SetUniform(const std::string& name, float value) const;
		void SetUniform(const std::string& name, const glm::vec3& value) const;
		void SetUniform(const std::string& name, const glm::mat4& value) const;
	private:
		unsigned int m_ID;
	};

}



