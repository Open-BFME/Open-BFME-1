// ?getTerrainTexture@WorldHeightMap@@QAE?AVTerrainTextureRef@@XZ
// partial score=0.22 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0074CFA0. BFME texture setup with a counted return handle.

typedef unsigned char UnsignedByte;

class TextureBaseClass
{
public:
	void Release_Ref(void);
	int m_unreconstructed_00;
	unsigned short m_numRefs;
};

class TerrainTextureRef
{
public:
	TerrainTextureRef(TextureBaseClass *p) : m_p(p)
	{
		if (m_p)
			++m_p->m_numRefs;
	}

	TextureBaseClass *m_p;
};

class Rva006D51B0TextureRef
{
public:
	Rva006D51B0TextureRef(void) : m_ptr(0) {}
	~Rva006D51B0TextureRef(void);

	TextureBaseClass *m_ptr;
};

#pragma comment(linker, "/alternatename:??1Rva006D51B0TextureRef@@QAE@XZ=?b_00728c40@@YAXXZ")

class Rva006D51B0
{
public:
	Rva006D51B0(unsigned, unsigned);

	Rva006D51B0TextureRef m_texture;
};

class BfmeSrcSJ
{
public:
	void *m_bfmeObjSJ;
};

class Rva0074CFA0HostBase
{
public:
	~Rva0074CFA0HostBase(void);

	void *m_bfmeTexSJ;
};

#pragma comment(linker, "/alternatename:??1Rva0074CFA0HostBase@@QAE@XZ=?b_00749780@@YAXXZ")

class Rva0074CFA0Host : public Rva0074CFA0HostBase
{
public:
	Rva0074CFA0Host(BfmeSrcSJ *src);
};

#pragma comment(linker, "/alternatename:??0Rva0074CFA0Host@@QAE@PAVBfmeSrcSJ@@@Z=??0BfmeHostSJ@@QAE@PAVBfmeSrcSJ@@@Z")

class Rva006D6050Guard
{
public:
	~Rva006D6050Guard(void);
};

#pragma comment(linker, "/alternatename:??1Rva006D6050Guard@@QAE@XZ=?b_00749790@@YAXXZ")

class Rva006D6050
{
public:
	Rva006D6050(int, int);
	void init(int, int, int, int, int, int);

	TextureBaseClass *m_texture;
	Rva006D6050Guard m_guard;
};

class Rva0074CFA0MapWork
{
public:
	int updateTileTexturePositions(int *edgeHeight);
};

#pragma comment(linker, "/alternatename:?updateTileTexturePositions@Rva0074CFA0MapWork@@QAEHPAH@Z=?resetRenderStates@BfmeRenderStateLists@@QAEHH@Z")

class Rva0074CFA0TerrainRef
{
public:
	int update(void *map);
};

#pragma comment(linker, "/alternatename:?update@Rva0074CFA0TerrainRef@@QAEHPAX@Z=?m@Gen_006d5390@@QAEHH@Z")

class Rva0074CFA0EdgeRef
{
public:
	int update(void *map);
};

#pragma comment(linker, "/alternatename:?update@Rva0074CFA0EdgeRef@@QAEHPAX@Z=?d_006d60d0@@YAXXZ")

class WorldHeightMap
{
public:
	TerrainTextureRef getTerrainTexture(void);
	bool getFlipState(int xIndex, int yIndex);

private:
	char m_base[8];
	int m_width;
	int m_height;
	char m_gap10[0x18];
	UnsignedByte *m_cellFlipState;
	char m_gap2c[8];
	int m_flipStateWidth;
	char m_gap38[0x1208c];
	Rva006D51B0TextureRef m_terrainTex;
	int m_terrainTexHeight;
	Rva006D51B0TextureRef m_alphaTerrainTex;
	int m_alphaTexHeight;
	Rva006D51B0TextureRef m_alphaEdgeTex;
	int m_alphaEdgeHeight;
};

#pragma comment(linker, "/alternatename:?getFlipState@WorldHeightMap@@QAE_NHH@Z=?d_0074cdd0@@YAXXZ")

extern "C" int __cdecl sprintf(char *, const char *, ...);

TerrainTextureRef WorldHeightMap::getTerrainTexture(void)
{
	if (m_terrainTex.m_ptr == 0)
	{
		int edgeHeight;
		int height = reinterpret_cast<Rva0074CFA0MapWork *>(this)->updateTileTexturePositions(&edgeHeight);
		int pow2Height = 1;
		while (pow2Height < height)
			pow2Height *= 2;

		{
			Rva006D51B0 terrain(pow2Height, 0x19);
			TextureBaseClass *texture = terrain.m_texture.m_ptr;
			if (texture)
				++texture->m_numRefs;
			if (m_terrainTex.m_ptr)
				m_terrainTex.m_ptr->Release_Ref();
			m_terrainTex.m_ptr = texture;
		}

		m_terrainTexHeight = reinterpret_cast<Rva0074CFA0TerrainRef *>(&m_terrainTex)->update(this);
		char buf[64];
		sprintf(buf, "Base tex height %d\n", pow2Height);

		{
			Rva0074CFA0Host host(reinterpret_cast<BfmeSrcSJ *>(&m_terrainTex));
			if (m_alphaTerrainTex.m_ptr)
				m_alphaTerrainTex.m_ptr->Release_Ref();
			m_alphaTerrainTex.m_ptr = reinterpret_cast<TextureBaseClass *>(host.m_bfmeTexSJ);
		}

		pow2Height = 1;
		while (pow2Height < edgeHeight)
			pow2Height *= 2;

		{
			Rva006D6050 edge(pow2Height, 3);
			TextureBaseClass *texture = edge.m_texture;
			if (texture)
				++texture->m_numRefs;
			if (m_alphaEdgeTex.m_ptr)
				m_alphaEdgeTex.m_ptr->Release_Ref();
			m_alphaEdgeTex.m_ptr = texture;
		}

		m_alphaEdgeHeight = reinterpret_cast<Rva0074CFA0EdgeRef *>(&m_alphaEdgeTex)->update(this);

		for (int y = 0; y < m_height - 1; ++y)
		{
			for (int x = 0; x < m_width - 1; ++x)
			{
				bool flipForBlend = getFlipState(x, y);
				m_cellFlipState[y * m_flipStateWidth + (x >> 3)] |=
					static_cast<UnsignedByte>(flipForBlend << (x & 7));
			}
		}
	}

	return TerrainTextureRef(m_terrainTex.m_ptr);
}
