// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x0072F2B0: TerrainTracksRenderObjClass::init at the
// retail 0x1304-byte layout and BFME texture-handle ABI.

typedef unsigned char Bool;

class TextureClass;

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int mipCount, int format);

static inline void BFMEAssignTerrainTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

class TerrainTracksRenderObjClass
{
public:
	void init(float width, float length, const char *textureName);

private:
	unsigned char m_base[8];
	TextureClass *m_stageZeroTexture;              // +0x0008
	int m_topIndex;                                // +0x000C
	int m_bottomIndex;                             // +0x0010
	int m_activeEdgeCount;                         // +0x0014
	unsigned char m_edgesAndAnchor[0x12E4 - 0x18];
	int m_totalEdgesAdded;                         // +0x12E4
	int m_ownerState;                              // +0x12E8
	Bool m_haveAnchor;                             // +0x12EC
	unsigned char m_tail0[3];
	float m_width;                                 // +0x12F0
	float m_length;                                // +0x12F4
	unsigned char m_tail1;
	Bool m_haveCap;                                // +0x12F9
};

void TerrainTracksRenderObjClass::init(float width, float length, const char *textureName)
{
	m_width = width;
	m_haveAnchor = false;
	m_haveCap = true;
	m_ownerState = 0;
	m_totalEdgesAdded = 0;
	m_topIndex = 0;
	m_bottomIndex = 0;
	m_activeEdgeCount = 0;
	m_length = length;

	BFMEAssignTerrainTrackTexture(
		m_stageZeroTexture,
		BFMEGetWaterTrackTexture((char *)textureName, 0, 0));
}
