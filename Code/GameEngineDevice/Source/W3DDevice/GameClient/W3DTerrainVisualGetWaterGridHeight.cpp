// cl: /DNDEBUG /MD /EHsc
// readable body of ?getWaterGridHeight@W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	Bool worldToGridSpace(float worldX, float worldY, float &gridX, float &gridY);
	void getGridVertexHeight(int x, int y, float *height);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisual.h
class W3DTerrainVisual
{
public:
	virtual Bool getWaterGridHeight(float worldX, float worldY, float *height);

private:
	unsigned char m_basePadding[0x0C];
	void *m_terrainRenderObject;
	WaterRenderObjClass *m_waterRenderObject;
	void *m_logicHeightMap;
	Bool m_isWaterGridRenderingEnabled;
};

Bool W3DTerrainVisual::getWaterGridHeight(float worldX, float worldY, float *height)
{
	float gridX;
	float gridY;
	if (m_isWaterGridRenderingEnabled) {
		WaterRenderObjClass *water = m_waterRenderObject;
		if (water && water->worldToGridSpace(worldX, worldY, gridX, gridY)) {
			water->getGridVertexHeight(static_cast<int>(gridX),
				static_cast<int>(gridY), height);
			return 1;
		}
	}
	return 0;
}
