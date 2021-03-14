#pragma once

namespace Loco {
	
	class Shader
	{
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		virtual ~Shader();

		void Active() const;
		void UnActive() const;
		
		unsigned int ID() const { return m_ID; }

		void SetUniform(const std::string& name, bool value) const;
		void SetUniform(const std::string& name, int value) const;
		void SetUniform(const std::string& name, float value) const;
	private:
		unsigned int m_ID;
	};

}



