// cl: /DNDEBUG /MD /EHsc
// readable body of ?getUVForNdx@WorldHeightMap@@IAEXHPAM000_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp
// Open-BFME: WorldHeightMap::getUVForNdx, retail 0x00747490, 248 bytes.
//
// The reference's body unchanged, with EVAL_TILING_MODES off. What the bytes
// add is the numbers:
//
//   * m_sourceTiles sits at this+0xA4 and m_terrainTexHeight at this+0x120C8;
//   * TileData::m_tileLocationInTexture is at +0x555C, two Ints, which is why
//     both halves load through fild;
//   * TILE_PIXEL_EXTENT is the 64.0f at 0x0111E2BC;
//   * TEXTURE_WIDTH is 2048 -- the divide is a multiply by the exact
//     reciprocal 0.00048828125 at 0x01121AE4, which MSVC only does for a
//     power of two, while the divide by m_terrainTexHeight stays an fdivr
//     because that one is a member.
//
// The quadrant tail is the reference's: both midpoints computed first, then
// the y test before the x test, with `/2` folded to the 0.5f at 0x0107533C.

#define NULL 0

typedef int Int;
typedef short Short;
typedef float Real;
typedef bool Bool;

enum { NUM_SOURCE_TILES = 1024 };

#define TILE_PIXEL_EXTENT 64
#define TEXTURE_WIDTH 2048

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/TileData.h
class TileData
{
public:
	char m_bfmeTileData[0x555C];				// the mip chain
	ICoord2D m_tileLocationInTexture;			// +0x555C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
protected:
	void getUVForNdx(Int tileNdx, float *minU, float *minV, float *maxU, float*maxV, Bool fullTile);

	char m_bfmeHead[0xA4];					// this+0x00 .. +0xA3
	TileData *m_sourceTiles[NUM_SOURCE_TILES];		// this+0xA4
	char m_bfmeMid[0x120C8 - 0xA4 - NUM_SOURCE_TILES * 4];
	Int m_terrainTexHeight;					// this+0x120C8
};

void WorldHeightMap::getUVForNdx(Int tileNdx, float *minU, float *minV, float *maxU, float*maxV, Bool fullTile)
{
	Short baseNdx = tileNdx>>2;
	if (m_sourceTiles[baseNdx] == NULL) {
		// Missing texture.
		*minU = *minV = *maxU = *maxV = 0.0f;
		return;
	}
	ICoord2D pos = m_sourceTiles[baseNdx]->m_tileLocationInTexture;
	*minU = pos.x;
	*minV = pos.y;
	*maxU = *minU+TILE_PIXEL_EXTENT; 
	*maxV = *minV+TILE_PIXEL_EXTENT;
	*minU/=TEXTURE_WIDTH;
	*minV/=m_terrainTexHeight;
	*maxU/=TEXTURE_WIDTH;
	*maxV/=m_terrainTexHeight;
	if (!fullTile) {
		// Tiles are 64x64 pixels, height grids map to 32x32. 
		// So get the proper quadrant of the tile.
		Real midX = (*minU+*maxU)/2;
		Real midY = (*minV+*maxV)/2;
		if (tileNdx&2) {		// y's are flipped.
			*maxV = midY;
		} else {
			*minV = midY;
		}
		if (tileNdx&1) {
			*minU = midX;
		} else {
			*maxU = midX;
		}
	}
}
