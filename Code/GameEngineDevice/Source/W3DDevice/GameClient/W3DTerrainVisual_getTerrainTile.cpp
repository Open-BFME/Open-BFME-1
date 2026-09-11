// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// BFME W3DTerrainVisual::getTerrainTile, retail 0x00731760, 126 bytes.
//
// Identity comes from the W3DTerrainVisual Snapshot vtable slot 8 pin.  The
// body reads the BFME height-map member at +0x18, obtains an AsciiString by
// value, then passes that value to the already matched TerrainTypeCollection
// lookup.  Keep the narrow string as the canonical inline StringBase view so
// the returned temporary and its caller-side cleanup retain the retail ABI.

#include "StringInline.h"

typedef float Real;

class TerrainType;

class WorldHeightMap
{
public:
	AsciiString getTerrainNameAt(Real x, Real y);
};

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
};

extern TerrainTypeCollection *TheTerrainTypes;

// The BFME retail method is reached through the existing incremental-link
// thunk.  The callee itself is not part of this conversion.
#pragma comment(linker, "/alternatename:?getTerrainNameAt@WorldHeightMap@@QAE?AVAsciiString@@MM@Z=?j_0000a80d@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTerrain@TerrainTypeCollection@@QAEPAVTerrainType@@VAsciiString@@@Z=?j_0000dbd9@@YAXXZ")

class W3DTerrainVisual
{
public:
	virtual TerrainType *getTerrainTile(Real x, Real y);

private:
	unsigned char m_baseAndUnusedFields[0x14];
	WorldHeightMap *m_logicHeightMap; // +0x18
};

TerrainType *W3DTerrainVisual::getTerrainTile(Real x, Real y)
{
	TerrainType *tile = 0;

	if (m_logicHeightMap)
	{
		AsciiString tileName = m_logicHeightMap->getTerrainNameAt(x, y);
		tile = TheTerrainTypes->findTerrain(tileName);
	}

	return tile;
}
