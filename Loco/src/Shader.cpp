#include "stdafx.h"
#include "Shader.h"

#include <glad/glad.h>

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
{
	std::string vertStr, fragStr;
	std::ifstream vertSrcFile, fragSrcFile;

	vertSrcFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragSrcFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertSrcFile.open(vertPath);
		fragSrcFile.open(fragPath);
		std::stringstream vertSrcStream, fragSrcStream;
		vertSrcStream << vertSrcFile.rdbuf();
		fragSrcStream << fragSrcFile.rdbuf();
		vertSrcFile.close();
		fragSrcFile.close();
		vertStr = vertSrcStream.str();
		fragStr = fragSrcStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertSrc = vertStr.c_str();
	const char* fragSrc = fragStr.c_str();

	unsigned int vertShader, fragShader;
	int success;
	char infoLog[512];

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSrc, NULL);
	glCompileShader(vertShader);

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::CPMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::CPMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertShader);
	glAttachShader(m_ID, fragShader);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::Active()
{
	glUseProgram(m_ID);
}

void Shader::UnActive()
{
	glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::SetUniform(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
