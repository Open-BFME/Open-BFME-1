// ?reacquireTexture@Rva00729180Terrain@@QAEEXZ
// partial score=0.7 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00729180: reacquire the terrain background texture and its filter.

typedef unsigned char Bool;

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TerrainFilter
{
public:
	unsigned char m_pad00[0x0c];
	int m_uAddress;
	int m_vAddress;
};

class TerrainTexture
{
public:
	void Release_Ref();
};

class TerrainTextureHandle
{
public:
	TerrainTexture *m_p;

	~TerrainTextureHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}
};

class TerrainTextureSlot
{
public:
	TerrainFilter *getFilter();
	void update();

	TerrainTextureSlot &operator=(const TerrainTextureHandle &source)
	{
		if (source.m_p)
			++*(unsigned short *)((unsigned char *)source.m_p + 4);
		if (m_p)
			m_p->Release_Ref();
		m_p = source.m_p;
		return *this;
	}

	TerrainTexture *m_p;
};

class WorldHeightMap
{
public:
	TerrainTextureHandle getFlatTexture(int x, int y, int width,
		int format, int mipCount);
};

class GlobalData
{
public:
	unsigned char m_pad00[0xecc];
	int m_textureReductionFactor;
};

extern GlobalData *TheWritableGlobalData;

class Rva00729180Terrain
{
public:
	Bool reacquireTexture();

private:
	int m_state;
	unsigned char m_pad04[0x2c];
	TerrainTextureSlot m_texture;
	int m_textureType;
	unsigned char m_pad38[0x08];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad50[0x24];
	unsigned char m_refresh;
};

// ?reacquireTexture@Rva00729180Terrain@@QAEEXZ
Bool Rva00729180Terrain::reacquireTexture()
{
	TerrainTextureSlot *texture;
	if (m_state != 2)
	{
		if (m_textureType == 4 ||
			TheWritableGlobalData->m_textureReductionFactor)
		{
			texture = &m_texture;
			if (texture->m_p == 0)
			{
				*texture = m_map->getFlatTexture(
					m_xOrigin, m_yOrigin, m_width, 0x20, 0x19);
				texture->getFilter()->m_uAddress = 1;
				texture->getFilter()->m_vAddress = 1;
				if (m_refresh)
					texture->update();
				return 1;
			}
		}
		return 0;
	}
	if (m_texture.m_p)
	{
		m_texture.m_p->Release_Ref();
		m_texture.m_p = 0;
	}
	return 0;
}
