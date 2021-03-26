#pragma once

#include <glad/glad.h>

namespace Loco {

	class Texture
		{
	public:
		
		enum class Type
		{
			NONE ,DIFFUSE, SPECULAR, NORMAL
		};

		Texture();
		Texture(const std::string& texPath, Type type);
		Texture(const char* texPath, Type type);
		Texture(int width, int height);
		virtual ~Texture();

		void Load(const std::string& path, unsigned target = GL_TEXTURE_2D);
		void Load(const char* path, unsigned target = GL_TEXTURE_2D);
		void UnLoad();

		void Bind(unsigned target = GL_TEXTURE_2D);
		void UnBind(unsigned target = GL_TEXTURE_2D);
		void Active(int index = 0) const;

		unsigned int GetID() const { return m_ID; }
		int Channels() const { return m_Channels; }
		int Width() const { return m_Width; }
		int Height() const { return m_Height; }
		
		Type GetType() const { return m_type; }
	protected:
		unsigned int m_ID;
		std::string m_Path;
		Type m_type;
		int m_Width;
		int m_Height;
		int m_Channels;
	};

}


