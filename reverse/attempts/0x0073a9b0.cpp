// ?d_0073a9b0@@YAXXZ
// partial score=0.75 date=2026-09-08

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

float getHeightAroundPos(float x, float y)
{
	float terrainHeight = TheTerrainLogic->getGroundHeight(x, y);
	float terrainHeightMax = terrainHeight;
	terrainHeightMax = maxHeight(terrainHeightMax, TheTerrainLogic->getGroundHeight(
		x + TheWritableGlobalData->m_terrainSampleSize,
		y - TheWritableGlobalData->m_terrainSampleSize));

	terrainHeightMax = maxHeight(terrainHeightMax, TheTerrainLogic->getGroundHeight(
		x - TheWritableGlobalData->m_terrainSampleSize,
		y - TheWritableGlobalData->m_terrainSampleSize));

	terrainHeightMax = maxHeight(terrainHeightMax, TheTerrainLogic->getGroundHeight(
		x + TheWritableGlobalData->m_terrainSampleSize,
		y + TheWritableGlobalData->m_terrainSampleSize));

	terrainHeightMax = maxHeight(terrainHeightMax, TheTerrainLogic->getGroundHeight(
		x - TheWritableGlobalData->m_terrainSampleSize,
		y + TheWritableGlobalData->m_terrainSampleSize));

	return terrainHeightMax;
}
