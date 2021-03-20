#pragma once

namespace Loco {

	class Texture
		{
	public:
		
		enum class Type
		{
			NONE ,DIFFUSE, SPECULAR, NORMAL
		};

		Texture(const std::string& texPath, Type type);
		Texture(const char* texPath, Type type);
		virtual ~Texture();

		void Active(int index = 0) const;

		unsigned int ID() const { return m_ID; }
		int Channels() const { return m_Channels; }
		int Width() const { return m_Width; }
		int Height() const { return m_Height; }
		
		Type GetType() const { return m_type; }
	private:
		unsigned int m_ID;
		std::string m_Path;
		Type m_type;
		int m_Width;
		int m_Height;
		int m_Channels;
	};

}


