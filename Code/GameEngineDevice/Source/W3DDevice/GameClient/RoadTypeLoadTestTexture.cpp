// cl: /DNDEBUG /DWIN32 /DLOAD_TEST_ASSETS /MD /EHsc
// BFME retail 0x00708200: RoadType::loadTestTexture.

typedef int Int;
typedef unsigned char Bool;
typedef unsigned short UnsignedShort;
typedef char Char;

class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(UnsignedShort *)((Char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

class AsciiString
{
public:
	Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}

	Char *m_data;
};

class Gen_00920a60
{
public:
	void m(Int value);

	Char m_pad00[0x0c];
	Int m_uAddress;
	Int m_vAddress;
};

class ShroudFilter : public Gen_00920a60
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	TextureClass *m_texture;
};

class RoadType
{
public:
	void loadTestTexture(void);

private:
	TextureClass *m_roadTexture;
	void *m_vertexRoad;
	void *m_indexRoad;
	Int m_numRoadVertices;
	Int m_numRoadIndices;
	Int m_uniqueID;
	Bool m_isAutoLoaded;
	Char m_pad19[3];
	Int m_stackingOrder;
	AsciiString m_texturePath;
};

void RoadType::loadTestTexture(void)
{
	if (!m_isAutoLoaded || m_uniqueID <= 0 || m_texturePath.m_data == 0 ||
		*(UnsignedShort *)(m_texturePath.m_data + 4) == 0)
		return;

	BFMEAssignWaterTrackTexture(m_roadTexture,
		BFMEGetWaterTrackTexture(m_texturePath.str(), 3, 0));

	((ShroudTexture *)this)->getFilter()->m(2);
	((ShroudTexture *)this)->getFilter()->m_uAddress = 0;
	((ShroudTexture *)this)->getFilter()->m_vAddress = 0;
}
