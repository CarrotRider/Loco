#pragma once
#include "Core.h"

namespace Loco {

	struct InternalFormat
	{
		const static int CompressedRed;
		const static int CompressedRedRGTC1;
		const static int CompressedRG;
		const static int CompressedRGB;
		const static int CompressedRGBA;
		const static int CompressedRGRGTC2;
		const static int CompressedSignedRedRGTC1;
		const static int CompressedSignedRGRGTC2;
		const static int CompressedSRGB;
		const static int DepthStencil;
		const static int Depth24Stencil8;
		const static int Depth32FStencil8;
		const static int DepthComponent;
		const static int DepthComponent16;
		const static int DepthComponent24;
		const static int DepthComponent32F;
		const static int R16F;
		const static int R16I;
		const static int R16SNorm;
		const static int R16UI;
		const static int R32F;
		const static int R32I;
		const static int R32UI;
		const static int R3G3B2;
		const static int R8;
		const static int R8I;
		const static int R8SNorm;
		const static int R8UI;
		const static int Red;
		const static int RG;
		const static int RG16;
		const static int RG16F;
		const static int RG16SNorm;
		const static int RG32F;
		const static int RG32I;
		const static int RG32UI;
		const static int RG8;
		const static int RG8I;
		const static int RG8SNorm;
		const static int RG8UI;
		const static int RGB;
		const static int RGB10;
		const static int RGB10A2;
		const static int RGB12;
		const static int RGB16;
		const static int RGB16F;
		const static int RGB16I;
		const static int RGB16UI;
		const static int RGB32F;
		const static int RGB32I;
		const static int RGB32UI;
		const static int RGB4;
		const static int RGB5;
		const static int RGB5A1;
		const static int RGB8;
		const static int RGB8I;
		const static int RGB8UI;
		const static int RGB9E5;
		const static int RGBA;
		const static int RGBA12;
		const static int RGBA16;
		const static int RGBA16F;
		const static int RGBA16I;
		const static int RGBA16UI;
		const static int RGBA2;
		const static int RGBA32F;
		const static int RGBA32I;
		const static int RGBA32UI;
		const static int RGBA4;
		const static int RGBA8;
		const static int RGBA8UI;
		const static int SRGB8;
		const static int SRGB8A8;
		const static int SRGBA;
	};

	struct Format
	{
		const static int RED;
		const static int RGB;
		const static int BGR;
		const static int RGBA;
		const static int BGRA;
	};

	struct DataType
	{
		const static int Byte;
		const static int UnsignedByte;
		const static int Short;
		const static int UnsignedShort;
		const static int Int;
		const static int UnsignedInt;
		const static int Float;
		const static int Double;

		const static int UnsignedByte332;
		const static int UnsignedByte233Rev;
		const static int UnsignedShort565;
		const static int UnsignedShort565Rev;
		const static int UnsignedShort4444;
		const static int UnsignedShort4444Rev;
		const static int UnsignedShort5551;
		const static int UnsignedShort1555Rev;
		const static int UnsignedInt8888;
		const static int UnsignedInt8888Rev;
		const static int UnsignedInt101010102;
	};
	
	struct Filter
	{
		const static int Nearest;
		const static int Linear;
		const static int NearestMipmapNearest;
		const static int LinearMipmapNearest;
		const static int NearestMipmapLinear;
		const static int LinearMipmapLinear;
	};

	struct Wrapping
	{
		const static int ClampEdge;
		const static int ClampBorder;
		const static int Repeat;
		const static int MirroredRepeat;
	};

	class LOCO_API Texture
		{
	public:

		enum class Type
		{
			NONE ,DIFFUSE, SPECULAR, NORMAL
		};

		Texture();
		Texture(int width, int height);
		Texture(const std::string& texPath, Type type);
		Texture(const char* texPath, Type type);
		virtual ~Texture();

		void Image2D(const void* data, int type, int format,
			unsigned width, unsigned height, int internalFormat);

		void SetWrapping(int s);
		void SetWrapping(int s, int t);
		void SetWrapping(int s, int t, int r);

		void SetFilters(int min, int mag);

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


