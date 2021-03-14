#pragma once

namespace Loco {

	class Texture
	{
	public:
		Texture(const std::string& texPath);
		virtual ~Texture();

		void Active(int index = 0) const;

		unsigned int ID() const { return m_ID; }
		int Channels() const { return m_Channels; }
		int Width() const { return m_Width; }
		int Height() const { return m_Height; }
	private:
		unsigned int m_ID;
		int m_Width;
		int m_Height;
		int m_Channels;
	};

}


