// ?getAlphaTerrainTexture@WorldHeightMap@@QAE?AVTerrainTextureRef@@XZ
// ?getEdgeTerrainTexture@WorldHeightMap@@QAE?AVTerrainTextureRef@@XZ
// cl: /O2 /GX-
//
// Retail 0x0074D210 and 0x0074D270, the pair of lazy terrain-texture getters
// upstream spells at reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp:2213-2227:
//
//     TextureClass *WorldHeightMap::getAlphaTerrainTexture(void)
//     { if (m_alphaTerrainTex == NULL) getTerrainTexture(); return m_alphaTerrainTex; }
//     TextureClass *WorldHeightMap::getEdgeTerrainTexture(void)
//     { if (m_alphaEdgeTex == NULL) getTerrainTexture(); return m_alphaEdgeTex; }
//
// Three things pin the identity together.  The two members sit at +0x120CC and
// +0x120D4, eight bytes apart, exactly as upstream declares them -- m_terrainTex,
// m_terrainTexHeight, m_alphaTerrainTex, m_alphaTexHeight, m_alphaEdgeTex -- so
// the Int height field falls between them (WorldHeightMap.h:169-178).  The two
// bodies are 0x60 apart in the same order as those two upstream functions.  And
// they sit inside the WorldHeightMap.cpp code run: getPointerToTileData is at
// 0x0074C920 and the short-to-int copy at 0x0074D6A0.
//
// BFME changed only the return convention: instead of the raw TextureClass* it
// returns a counted handle, so the getter takes a reference on the way out and
// drops the one getTerrainTexture() handed back.
//
// The volatile guard local and the volatile members are what hold retail's
// zero-store schedule; without them MSVC hoists the load past the null test.

class TextureBaseClass
{
public:
	void Release_Ref();
	int m_unreconstructed_00;
	unsigned short m_numRefs;
};

// The by-value counted handle BFME returns from the texture getters.
class TerrainTextureRef
{
public:
	TerrainTextureRef(TextureBaseClass *p);
	TextureBaseClass *m_p;
};

inline TerrainTextureRef::TerrainTextureRef(TextureBaseClass *p) : m_p(p)
{
	if (m_p)
		++m_p->m_numRefs;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	TerrainTextureRef getTerrainTexture();
	TerrainTextureRef getAlphaTerrainTexture();
	TerrainTextureRef getEdgeTerrainTexture();

private:
	char m_pad[0x120CC];
	TextureBaseClass * volatile m_alphaTerrainTex;	// +0x120CC
	int m_alphaTexHeight;							// +0x120D0
	TextureBaseClass * volatile m_alphaEdgeTex;		// +0x120D4
};

TerrainTextureRef WorldHeightMap::getAlphaTerrainTexture()
{
	volatile int guard = 0;
	TextureBaseClass *alpha = m_alphaTerrainTex;
	if (alpha == 0)
	{
		TerrainTextureRef tmp = getTerrainTexture();
		if (tmp.m_p)
			tmp.m_p->Release_Ref();
	}
	return TerrainTextureRef(m_alphaTerrainTex);
}

TerrainTextureRef WorldHeightMap::getEdgeTerrainTexture()
{
	volatile int guard = 0;
	if (m_alphaEdgeTex == 0)
	{
		TerrainTextureRef tmp = getTerrainTexture();
		if (tmp.m_p)
			tmp.m_p->Release_Ref();
	}
	return TerrainTextureRef(m_alphaEdgeTex);
}
