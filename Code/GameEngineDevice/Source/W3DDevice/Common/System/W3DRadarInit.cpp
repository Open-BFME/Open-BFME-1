// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "Common/Radar.h"
#include "GameClient/Image.h"

class Rva006D6050
{
public:
	void init(unsigned width, unsigned height, unsigned format,
		unsigned mip_levels, unsigned pool, unsigned render_target);

	void *m_texture;
};

class ShroudFilter
{
public:
	void setMin(unsigned value) { min_filter = value; }
	void setMag(unsigned value) { mag_filter = value; }
	void setAddressU(unsigned value) { address_u = value; }
	void setAddressV(unsigned value) { address_v = value; }
	unsigned min_filter;
	unsigned mag_filter;
	unsigned unused;
	unsigned address_u;
	unsigned address_v;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
	void *m_texture;
};

struct Rva005D2330TextureRef
{
	void *m_value;
};

class Rva005D2330TextureRefOwner
{
public:
	void assign(const Rva005D2330TextureRef &source);
};

class Gen006C1A20ImageState
{
public:
	void initialize();
};

class W3DRadar : public Radar
{
public:
	virtual void init();

protected:
	void initializeTextureFormats();

private:
	char m_padRadarBase[0x146c - sizeof(Radar)];
	Bool m_bfmeMapChanged;
	char m_pad146d[3];
	unsigned m_terrainTextureFormat;
	Image *m_terrainImage;
	ShroudTexture m_terrainTexture;
	ShroudTexture m_texture147c;
	unsigned m_overlayTextureFormat;
	Image *m_overlayImage;
	ShroudTexture m_overlayTexture;
	unsigned m_shroudTextureFormat;
	Image *m_shroudImage;
	ShroudTexture m_shroudTexture;
	unsigned m_borderShroudTextureFormat;
	Image *m_borderShroudImage;
	ShroudTexture m_borderShroudTexture;
	unsigned m_textureWidth;
	unsigned m_textureHeight;
};

void W3DRadar::init()
{
	ICoord2D size;
	Region2D uv;
	unsigned one = 1;

	initializeTextureFormats();

	reinterpret_cast<Rva006D6050 *>(&m_terrainTexture)->init(m_textureWidth, m_textureHeight,
		m_terrainTextureFormat, one, one, 0);
	reinterpret_cast<Rva006D6050 *>(&m_overlayTexture)->init(m_textureWidth, m_textureHeight,
		m_overlayTextureFormat, one, one, 0);
	reinterpret_cast<Rva006D6050 *>(&m_shroudTexture)->init(m_textureWidth, m_textureHeight,
		m_shroudTextureFormat, one, one, 0);
	ShroudTexture *shroud = &m_shroudTexture;
	shroud->getFilter()->setMin(4);
	shroud->getFilter()->setMag(4);
	shroud->getFilter()->setAddressU(one);
	shroud->getFilter()->setAddressV(one);

	reinterpret_cast<Rva006D6050 *>(&m_borderShroudTexture)->init(m_textureWidth, m_textureHeight,
		m_borderShroudTextureFormat, 1, 1, 0);
	ShroudTexture *border = &m_borderShroudTexture;
	border->getFilter()->setMin(4);
	border->getFilter()->setMag(4);

	m_terrainImage = ::new Image;
	reinterpret_cast<Gen006C1A20ImageState *>(this)->initialize();

	m_overlayImage = ::new Image;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	m_overlayImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	reinterpret_cast<Rva005D2330TextureRefOwner *>(m_overlayImage)->assign(
		*reinterpret_cast<const Rva005D2330TextureRef *>(&m_overlayTexture));
	m_overlayImage->setUV(&uv);
	m_overlayImage->setTextureWidth(m_textureWidth);
	m_overlayImage->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_overlayImage->setImageSize(&size);

	m_shroudImage = ::new Image;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	m_shroudImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	reinterpret_cast<Rva005D2330TextureRefOwner *>(m_shroudImage)->assign(
		*reinterpret_cast<const Rva005D2330TextureRef *>(&m_shroudTexture));
	m_shroudImage->setUV(&uv);
	m_shroudImage->setTextureWidth(m_textureWidth);
	m_shroudImage->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_shroudImage->setImageSize(&size);

	m_borderShroudImage = ::new Image;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	m_borderShroudImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	reinterpret_cast<Rva005D2330TextureRefOwner *>(m_borderShroudImage)->assign(
		*reinterpret_cast<const Rva005D2330TextureRef *>(&m_borderShroudTexture));
	m_borderShroudImage->setUV(&uv);
	m_borderShroudImage->setTextureWidth(m_textureWidth);
	m_borderShroudImage->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_borderShroudImage->setImageSize(&size);
}
