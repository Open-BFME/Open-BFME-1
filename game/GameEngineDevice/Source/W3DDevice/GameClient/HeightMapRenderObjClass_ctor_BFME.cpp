// cl: /O2 /Ob0

extern "C" char g_heightMapRenderObjVtableAtZero[];
extern "C" char g_heightMapRenderObjVtableAtEight[];
extern "C" char g_heightMapRenderObjVtableAtC8[];
extern "C" char g_heightMapRenderObjVtableAtCC[];

class HeightMapRenderObjClass;
extern HeightMapRenderObjClass *TheHeightMap;

class BaseHeightMapRenderObjClass
{
public:
	BaseHeightMapRenderObjClass(void) throw();
	char *volatile m_vtableAtZero;
	int m_baseField04;
};

class HeightMapRenderObjClass : public BaseHeightMapRenderObjClass
{
public:
	HeightMapRenderObjClass(int useDepthFade);

private:
	char *volatile m_vtableAtEight;
	char m_baseFields0C[0xBC];
	char *volatile m_vtableAtC8;
	char *volatile m_vtableAtCC;
	char m_baseFieldsD0[0x3004];
	int *volatile m_extraBlendTilePositions;
	volatile int m_numExtraBlendTiles;
	volatile int m_numVisibleExtraBlendTiles;
	volatile int m_extraBlendTilePositionsSize;
	void *volatile m_vertexBufferTiles;
	char m_renderFields30E8[0x10];
	volatile char m_useDepthFade;
	char m_renderFields30F9[0xB];
	volatile char m_renderMode;
	char m_padding3105[3];
	volatile int m_numVBTilesX;
	volatile int m_numVBTilesY;
	volatile int m_numVertexBufferTiles;
	char m_renderFields3114[0x60];
	volatile bool m_hasRenderResources;
	char m_padding3175[3];
	volatile int m_renderResourceCount;
};

HeightMapRenderObjClass::HeightMapRenderObjClass(int useDepthFade)
{
	char depthFade = useDepthFade;

	m_extraBlendTilePositions = 0;
	m_numExtraBlendTiles = 0;
	m_numVisibleExtraBlendTiles = 0;
	m_extraBlendTilePositionsSize = 0;
	m_vertexBufferTiles = 0;
	m_renderMode = 0;
	m_vtableAtZero = g_heightMapRenderObjVtableAtZero;
	m_vtableAtEight = g_heightMapRenderObjVtableAtEight;
	m_vtableAtC8 = g_heightMapRenderObjVtableAtC8;
	m_vtableAtCC = g_heightMapRenderObjVtableAtCC;
	m_useDepthFade = depthFade;
	m_numVBTilesX = 0;
	m_numVBTilesY = 0;
	m_numVertexBufferTiles = 0;
	m_hasRenderResources = false;
	m_renderResourceCount = 0;
	TheHeightMap = this;
}
