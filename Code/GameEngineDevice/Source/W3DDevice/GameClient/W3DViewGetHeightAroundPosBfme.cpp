// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
//
// BFME's W3DView.cpp variant of the upstream getHeightAroundPos helper.  The
// five samples and their max reduction are the same camera-height operation;
// BFME reads the corner offset from GlobalData rather than using ZH's 40.0f
// constant.  The balanced reduction is significant: it is the retail x87
// evaluation tree and avoids rounding the intermediate maxima through memory.

struct GlobalData
{
	char m_padding[0xe5c];
	float m_terrainSampleSize;
};

class TerrainLogic
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual float getGroundHeight(float x, float y, void *normal = 0) const;
};

extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;

__forceinline static float maxHeight(float first, float second)
{
	return first > second ? first : second;
}

// ?getHeightAroundPos@@YAMMM@Z
float getHeightAroundPos(float x, float y)
{
	float terrainHeight = TheTerrainLogic->getGroundHeight(x, y);
	return maxHeight(terrainHeight, maxHeight(
		maxHeight(
			TheTerrainLogic->getGroundHeight(
				x + TheWritableGlobalData->m_terrainSampleSize,
				y - TheWritableGlobalData->m_terrainSampleSize),
			TheTerrainLogic->getGroundHeight(
				x - TheWritableGlobalData->m_terrainSampleSize,
				y - TheWritableGlobalData->m_terrainSampleSize)),
		maxHeight(
			TheTerrainLogic->getGroundHeight(
				x + TheWritableGlobalData->m_terrainSampleSize,
				y + TheWritableGlobalData->m_terrainSampleSize),
			TheTerrainLogic->getGroundHeight(
				x - TheWritableGlobalData->m_terrainSampleSize,
				y + TheWritableGlobalData->m_terrainSampleSize))));
}
