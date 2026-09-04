// cl: /DNDEBUG /MD /EHsc
// Retail 0x006C1A20 initializes the radar image state and its texture view.

typedef unsigned int UnsignedInt;

struct ICoord2D
{
	int x;
	int y;
};

struct Region2D
{
	float loX;
	float loY;
	float hiX;
	float hiY;
};

class Image
{
public:
	UnsignedInt setStatus(UnsignedInt bit);
	void setUV(Region2D *uv) { if (uv) m_UVCoords = *uv; }
	void setTextureWidth(int width) { m_textureSize.x = width; }
	void setTextureHeight(int height) { m_textureSize.y = height; }
	void setImageSize(ICoord2D *size) { m_imageSize = *size; }

private:
	void *m_vtable;
	unsigned int m_name;
	unsigned int m_filename;
	ICoord2D m_textureSize;
	Region2D m_UVCoords;
	ICoord2D m_imageSize;
	void *m_rawTextureData;
	UnsignedInt m_status;
};

struct Rva005D2330TextureRef;

class Rva005D2330TextureRefOwner
{
public:
	void assign(const Rva005D2330TextureRef &source);
};

class Gen006C1A20ImageState
{
public:
	void initialize();

private:
	unsigned char m_padding00[0x1474];
	Image *m_image;
	unsigned int m_textureRef0;
	unsigned int m_textureRef1;
	unsigned char m_padding1480[0x24];
	unsigned int m_textureWidth;
	unsigned int m_textureHeight;
	unsigned char m_padding14ac[0x31];
	unsigned char m_imageReady;
};

void Gen006C1A20ImageState::initialize()
{
	Region2D uv;
	Rva005D2330TextureRef *texture;
	ICoord2D size;

	uv.loX = 0.0f;
	uv.loY = 1.0f;
	uv.hiX = 1.0f;
	uv.hiY = 0.0f;
	texture = reinterpret_cast<Rva005D2330TextureRef *>(
		reinterpret_cast<unsigned char *>(this) + 0x147c);
	if (!m_imageReady)
	{
		texture = reinterpret_cast<Rva005D2330TextureRef *>(
			reinterpret_cast<unsigned char *>(this) + 0x1478);
	}

	m_image->setStatus(2);
	reinterpret_cast<Rva005D2330TextureRefOwner *>(m_image)->assign(*texture);
	m_image->setUV(&uv);
	m_image->setTextureWidth(m_textureWidth);
	m_image->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_image->setImageSize(&size);
}
