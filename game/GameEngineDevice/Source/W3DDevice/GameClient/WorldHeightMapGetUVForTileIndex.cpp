#include <vector>

typedef int Int;
typedef short Short;
typedef float Real;
typedef bool Bool;

struct BfmeGlobalData0074BEB0
{
	char m_pad00[0x4d];
	Bool m_adjustCliffTextures;
};

struct BfmeCliffInfo0074BEB0
{
	Real u0;
	Real v0;
	Real u1;
	Real v1;
	Real u2;
	Real v2;
	Real u3;
	Real v3;
	Bool flip;
	Bool mutant;
	Short tileIndex;
};

struct BfmeTextureClass0074BEB0
{
	Int globalTextureClass;
	Int firstTile;
	Int numTiles;
	Int width;
	Int isBlendEdgeTile;
	void *name;
	Int positionX;
	Int positionY;
	char m_pad20[8];
};

struct BfmeWorldHeightMap0074BEB0
{
	char m_pad00[0x20];
	Int m_dataSize;
	char m_pad24[0x68];
	Short *m_tileNdxes;
	char m_pad90[4];
	Int *m_cliffInfoNdxes;
	char m_pad98[0x8014];
	std::vector<BfmeCliffInfo0074BEB0> m_cliffInfo;
	Int m_numTextureClasses;
	BfmeTextureClass0074BEB0 m_textureClasses[0x200];
	char m_padD0C0[0x5008];
	Int m_terrainTexHeight;
};

class WorldHeightMap
{
protected:
	char m_pad00[0x20];
	Int m_dataSize;
	char m_pad24[0x68];
	Short *m_tileNdxes;
	char m_pad90[4];
	Int *m_cliffInfoNdxes;
	char m_pad98[0x8014];
	std::vector<BfmeCliffInfo0074BEB0> m_cliffInfo;
	Int m_numTextureClasses;
	BfmeTextureClass0074BEB0 m_textureClasses[0x200];
	char m_padD0C0[0x5008];
	Int m_terrainTexHeight;

	void getUVForNdx(Int ndx, float *minU, float *minV, float *maxU,
		float *maxV, Bool fullTile);
	Bool getUVForTileIndex(Int ndx, Short tileNdx, float U[4],
		float V[4], Bool fullTile);
};

extern double Gen01085F58;
extern float Gen01121AE4;

extern const BfmeGlobalData0074BEB0 *TheGlobalData0074BEB0;

// ?getUVForTileIndex@WorldHeightMap@@IAE_NHFQAM0_N@Z
Bool WorldHeightMap::getUVForTileIndex(Int ndx, Short tileNdx, float U[4],
	float V[4], Bool fullTile)
{
	Real nU, nV, xU, xV;
	nU=nV=xU=xV = 0.0f;
	Int tilesPerRow = 2048/(2*64+0);
	tilesPerRow *= 4;

	if ((ndx<m_dataSize) && m_tileNdxes) {
		getUVForNdx(tileNdx, &nU, &nV, &xU, &xV, fullTile);
		U[0] = nU; U[1] = xU; U[2] = xU; U[3] = nU;
		V[0] = xV; V[1] = xV; V[2] = nV; V[3] = nV;
		if (TheGlobalData0074BEB0 && !TheGlobalData0074BEB0->m_adjustCliffTextures) {
			return false;
		}
		if (nU==Gen01085F58) {
			return false;
		}
		if (fullTile) {
			return false;
		}
		if (m_cliffInfoNdxes[ndx]) {
			BfmeCliffInfo0074BEB0 info = m_cliffInfo[m_cliffInfoNdxes[ndx]];
			Bool tilesMatch = false;
			register Int ndx1 = tileNdx>>2;
			register Int ndx2 = info.tileIndex>>2;
			register Int i;
			for (i=0; i<m_numTextureClasses; i++) {
				if (ndx1 >= m_textureClasses[i].firstTile && ndx1 < m_textureClasses[i].firstTile + m_textureClasses[i].numTiles) {
					tilesMatch = ndx2 >= m_textureClasses[i].firstTile && ndx2 < m_textureClasses[i].firstTile + m_textureClasses[i].numTiles;
					break;
				}
			}
			if (tilesMatch) {
				Real minU = m_textureClasses[i].positionX;
				Real maxV = m_textureClasses[i].positionY + m_textureClasses[i].width*64;
				minU*=Gen01121AE4;
				maxV/=m_terrainTexHeight;
				Real vFactor = 2048/m_terrainTexHeight;
				U[0] = info.u0+minU;
				U[1] = info.u1+minU;
				U[2] = info.u2+minU;
				U[3] = info.u3+minU;
				V[0] = info.v0*vFactor+maxV;
				V[1] = info.v1*vFactor+maxV;
				V[2] = info.v2*vFactor+maxV;
				V[3] = info.v3*vFactor+maxV;
				return info.flip;
			}
		}
	}
	return false;
}
