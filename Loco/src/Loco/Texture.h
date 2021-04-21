#pragma once
#include "Core.h"

namespace Loco {

	class LOCO_API Texture
		{
	public:
		
		enum class Type
		{
			NONE ,DIFFUSE, SPECULAR, NORMAL, SHADOW
		};

		Texture();
		Texture(const std::string& texPath, Type type);
		Texture(const char* texPath, Type type);
		Texture(int width, int height, Texture::Type type);
		virtual ~Texture();

		void Load(const std::string& path);
		void Load(const char* path);
		void UnLoad();

		void Bind();
		void UnBind();
		void Active(int index = 0) const;

		unsigned int GetID() const { return m_ID; }
		std::string GetPath() const { return m_Path; }
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


