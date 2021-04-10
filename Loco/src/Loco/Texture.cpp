#include "stdafx.h"
#include "Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Loco {

	Texture::Texture()
		: m_ID(0)
		, m_Path()
		, m_type(Type::NONE)
		, m_Channels(0)
		, m_Width(0)
		, m_Height(0)
	{

	}

	Texture::Texture(const std::string& texPath, Type type)
		: Texture(texPath.c_str(), type) {}

	Texture::Texture(const char* texPath, Type type)
		: m_ID(0)
		, m_Path(texPath)
		, m_type(type)
		, m_Channels(0)
		, m_Width(0)
		, m_Height(0)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(texPath,
			&m_Width, &m_Height, &m_Channels, 0);
		if (data)
		{
			switch (m_Channels)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			default:
				break;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	// 用于 FrameBuffer
	Texture::Texture(int width, int height)
		: m_ID(0)
		, m_Path()
		, m_type(Type::NONE)
		, m_Channels(0)
		, m_Width(width)
		, m_Height(height)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Texture::~Texture()
	{
		UnLoad();
	}

	void Texture::Load(const std::string& path)
	{
		Load(path.c_str());
	}

	void Texture::Load(const char* path)
	{
		glGenTextures(1, &m_ID);

		glBindTexture(GL_TEXTURE_2D, m_ID);

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path,
			&m_Width, &m_Height, &m_Channels, 0);

		if (data)
		{
			switch (m_Channels)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			default:
				break;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}

	void Texture::UnLoad()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Active(int index) const
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}