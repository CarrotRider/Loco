#include "stdafx.h"
#include "Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Loco {

	// InternalFormat
	const int InternalFormat::CompressedRed = GL_COMPRESSED_RED;
	const int InternalFormat::CompressedRedRGTC1 = GL_COMPRESSED_RED_RGTC1;
	const int InternalFormat::CompressedRG = GL_COMPRESSED_RG;
	const int InternalFormat::CompressedRGB = GL_COMPRESSED_RGB;
	const int InternalFormat::CompressedRGBA = GL_COMPRESSED_RGBA;
	const int InternalFormat::CompressedRGRGTC2 = GL_COMPRESSED_RG_RGTC2;
	const int InternalFormat::CompressedSignedRedRGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1;
	const int InternalFormat::CompressedSignedRGRGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2;
	const int InternalFormat::CompressedSRGB = GL_COMPRESSED_SRGB;
	const int InternalFormat::DepthStencil = GL_DEPTH_STENCIL;
	const int InternalFormat::Depth24Stencil8 = GL_DEPTH24_STENCIL8;
	const int InternalFormat::Depth32FStencil8 = GL_DEPTH32F_STENCIL8;
	const int InternalFormat::DepthComponent = GL_DEPTH_COMPONENT;
	const int InternalFormat::DepthComponent16 = GL_DEPTH_COMPONENT16;
	const int InternalFormat::DepthComponent24 = GL_DEPTH_COMPONENT24;
	const int InternalFormat::DepthComponent32F = GL_DEPTH_COMPONENT32F;
	const int InternalFormat::R16F = GL_R16F;
	const int InternalFormat::R16I = GL_R16I;
	const int InternalFormat::R16SNorm = GL_R16_SNORM;
	const int InternalFormat::R16UI = GL_R16UI;
	const int InternalFormat::R32F = GL_R32F;
	const int InternalFormat::R32I = GL_R32I;
	const int InternalFormat::R32UI = GL_R32UI;
	const int InternalFormat::R3G3B2 = GL_R3_G3_B2;
	const int InternalFormat::R8 = GL_R8;
	const int InternalFormat::R8I = GL_R8I;
	const int InternalFormat::R8SNorm = GL_R8_SNORM;
	const int InternalFormat::R8UI = GL_R8UI;
	const int InternalFormat::Red = GL_RED;
	const int InternalFormat::RG = GL_RG;
	const int InternalFormat::RG16 = GL_RG16;
	const int InternalFormat::RG16F = GL_RG16F;
	const int InternalFormat::RG16SNorm = GL_RG16_SNORM;
	const int InternalFormat::RG32F = GL_RG32F;
	const int InternalFormat::RG32I = GL_RG32I;
	const int InternalFormat::RG32UI = GL_RG32UI;
	const int InternalFormat::RG8 = GL_RG8;
	const int InternalFormat::RG8I = GL_RG8I;
	const int InternalFormat::RG8SNorm = GL_RG8_SNORM;
	const int InternalFormat::RG8UI = GL_RG8UI;
	const int InternalFormat::RGB = GL_RGB;
	const int InternalFormat::RGB10 = GL_RGB10;
	const int InternalFormat::RGB10A2 = GL_RGB10_A2;
	const int InternalFormat::RGB12 = GL_RGB12;
	const int InternalFormat::RGB16 = GL_RGB16;
	const int InternalFormat::RGB16F = GL_RGB16F;
	const int InternalFormat::RGB16I = GL_RGB16I;
	const int InternalFormat::RGB16UI = GL_RGB16UI;
	const int InternalFormat::RGB32F = GL_RGB32F;
	const int InternalFormat::RGB32I = GL_RGB32I;
	const int InternalFormat::RGB32UI = GL_RGB32UI;
	const int InternalFormat::RGB4 = GL_RGB4;
	const int InternalFormat::RGB5 = GL_RGB5;
	const int InternalFormat::RGB5A1 = GL_RGB5_A1;
	const int InternalFormat::RGB8 = GL_RGB8;
	const int InternalFormat::RGB8I = GL_RGB8I;
	const int InternalFormat::RGB8UI = GL_RGB8UI;
	const int InternalFormat::RGB9E5 = GL_RGB9_E5;
	const int InternalFormat::RGBA = GL_RGBA;
	const int InternalFormat::RGBA12 = GL_RGBA12;
	const int InternalFormat::RGBA16 = GL_RGBA16;
	const int InternalFormat::RGBA16F = GL_RGBA16F;
	const int InternalFormat::RGBA16I = GL_RGBA16I;
	const int InternalFormat::RGBA16UI = GL_RGBA16UI;
	const int InternalFormat::RGBA2 = GL_RGBA2;
	const int InternalFormat::RGBA32F = GL_RGBA32F;
	const int InternalFormat::RGBA32I = GL_RGBA32I;
	const int InternalFormat::RGBA32UI = GL_RGBA32UI;
	const int InternalFormat::RGBA4 = GL_RGBA4;
	const int InternalFormat::RGBA8 = GL_RGBA8;
	const int InternalFormat::RGBA8UI = GL_RGBA8UI;
	const int InternalFormat::SRGB8 = GL_SRGB8;
	const int InternalFormat::SRGB8A8 = GL_SRGB8_ALPHA8;
	const int InternalFormat::SRGBA = GL_SRGB_ALPHA;
	
	// Format
	const int Format::RED = GL_RED;
	const int Format::RGB = GL_RGB;
	const int Format::BGR = GL_BGR;
	const int Format::RGBA = GL_RGBA;
	const int Format::BGRA = GL_BGRA;

	// DataType
	const int DataType::Byte = GL_BYTE;
	const int DataType::UnsignedByte = GL_UNSIGNED_BYTE;
	const int DataType::Short = GL_SHORT;
	const int DataType::UnsignedShort = GL_UNSIGNED_SHORT;
	const int DataType::Int = GL_INT;
	const int DataType::UnsignedInt = GL_UNSIGNED_INT;
	const int DataType::Float = GL_FLOAT;
	const int DataType::Double = GL_DOUBLE;

	const int DataType::UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2;
	const int DataType::UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV;
	const int DataType::UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5;
	const int DataType::UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5;
	const int DataType::UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4;
	const int DataType::UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV;
	const int DataType::UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1;
	const int DataType::UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV;
	const int DataType::UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8;
	const int DataType::UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV;
	const int DataType::UnsignedInt101010102 = GL_UNSIGNED_INT_10_10_10_2;

	// Filter
	const int Filter::Nearest = GL_NEAREST;
	const int Filter::Linear = GL_LINEAR;
	const int Filter::NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST;
	const int Filter::LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST;
	const int Filter::NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR;
	const int Filter::LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR;

	// Wrapping
	const int Wrapping::ClampEdge = GL_CLAMP_TO_EDGE;
	const int Wrapping::ClampBorder = GL_CLAMP_TO_BORDER;
	const int Wrapping::Repeat = GL_REPEAT;
	const int Wrapping::MirroredRepeat = GL_MIRRORED_REPEAT;


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
	}


	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

	bool Texture::Load(const std::string& path, Type type)
	{
		return Load(path.c_str(), type);
	}

	bool Texture::Load(const char* path, Type type)
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);

		SetWrapping(Wrapping::Repeat, Wrapping::Repeat);
		SetFilters(Filter::Linear, Filter::Linear);

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(path,
			&m_Width, &m_Height, &m_Channels, 0);

		if (data)
		{
			switch (m_Channels)
			{
			case 3:
				Image2D(data, DataType::UnsignedByte, Format::RGB, m_Width, m_Height, InternalFormat::RGB);
				break;
			case 4:
				Image2D(data, DataType::UnsignedByte, Format::RGBA, m_Width, m_Height, InternalFormat::RGBA);
				break;
			default:
				break;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture: " << path << std::endl;
			stbi_image_free(data);
			return false;
		}
		stbi_image_free(data);
		return true;
	}

	/// void*, DataType, Format, int, int, InternalFormat
	void Texture::Image2D(const void* data, int type, int format, 
		unsigned width, unsigned height, int internalFormat)
	{
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)internalFormat, 
			width, height, 0, (GLenum)format, (GLenum)type, data);
		m_Width = width;
		m_Height = height;
		UnBind();
	}

	void Texture::SetWrapping(int s)
	{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s);
		UnBind();
	}

	void Texture::SetWrapping(int s, int t)
	{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)t);
		UnBind();
	}

	void Texture::SetWrapping(int s, int t, int r)
	{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, (GLint)r);
		UnBind();
	}

	void Texture::SetFilters(int min, int mag)
	{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)mag);
		UnBind();
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