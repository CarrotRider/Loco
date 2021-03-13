#pragma once

class Shader
{
public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void Active();
	void UnActive();
	unsigned int ID() { return m_ID; }

	void SetUniform(const std::string& name, bool value) const;
	void SetUniform(const std::string& name, int value) const;
	void SetUniform(const std::string& name, float value) const;
private:
	unsigned int m_ID;
};

