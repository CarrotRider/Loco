#include "stdafx.h"
#include "CubeTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Loco {

	CubeTexture::CubeTexture()
		: m_ID(0)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	}

	CubeTexture::~CubeTexture()
	{
		glDeleteTextures(1, &m_ID);
	}

	void CubeTexture::Load(const std::array<std::string, 6>& paths)
	{
		int width, height, channel;
		int len = paths.max_size();
		if (paths.size() != len)
		{
			std::cout << "ERROR::CUBE_TEXTURE::LOAD_FAILED::NUM_NOT_ENOUGH" << std::endl;
			return;
		}
		for (int i = 0; i < len; i++)
		{
			unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &channel, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "ERROR::CUBE_TEXTURE::LOAD_FAILED::PATH::" << paths[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void CubeTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	}

	void CubeTexture::UnBind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

}