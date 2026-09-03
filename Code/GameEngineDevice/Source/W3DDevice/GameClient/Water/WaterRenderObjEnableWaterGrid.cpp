// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean reconstruction of WaterRenderObjClass::enableWaterGrid at retail 0x007A1410.

typedef int Bool;
typedef int Int;
typedef long HRESULT;
typedef unsigned int UnsignedInt;

extern "C" void *memset(void *, int, unsigned int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterMeshData
{
public:
	float height;
	float velocity;
	unsigned char status;
	unsigned char preferredHeight;
};

class WaterResource
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void __stdcall Release_Ref(void) = 0;
};

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class WaterGridResetGuard
{
public:
	WaterGridResetGuard(void) { W3DRadarResetLock(); }
	~WaterGridResetGuard(void) { W3DRadarResetUnlock(); }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
	protected:
	char m_beforeVertexBuffers[0x124];
	WaterResource *m_vertexBuffer;
	WaterResource *m_indexBuffer;
	char m_beforeGrid[0x12c];
	WaterMeshData *m_meshData;
	UnsignedInt m_meshDataSize;
	char m_beforeGridFlag;
	bool m_doWaterGrid;
	char m_beforeDimensions[0x3e];
	Int m_gridCellsX;
	Int m_gridCellsY;
	char m_beforeRiverFlags[0x1c];
	bool m_drawingRiver;
	bool m_disableRiver;

	public:
	void reset(void);

	protected:
	HRESULT generateIndexBuffer(Int sizeX, Int sizeY);
	HRESULT generateVertexBuffer(Int sizeX, Int sizeY, Int vertexSize, bool doFill);
};

class WaterRenderObjClassEnableWaterGridShim : public WaterRenderObjClass
{
public:
	void enableWaterGrid(bool state);
};

void WaterRenderObjClassEnableWaterGridShim::enableWaterGrid(bool state)
{
	m_doWaterGrid = state;
	m_drawingRiver = false;
	m_disableRiver = false;

	if (state && m_meshData == 0)
	{
		m_meshDataSize = (m_gridCellsX + 1 + 2) * (m_gridCellsY + 1 + 2);
		m_meshData = new WaterMeshData[m_meshDataSize];
		memset(m_meshData, 0, sizeof(WaterMeshData) * (m_gridCellsX + 1 + 2) * (m_gridCellsY + 1 + 2));

		WaterGridResetGuard resetGuard;
		reset();

		if (m_vertexBuffer != 0)
		{
			m_vertexBuffer->Release_Ref();
			m_vertexBuffer = 0;
		}
		if (m_indexBuffer != 0)
		{
			m_indexBuffer->Release_Ref();
			m_indexBuffer = 0;
		}

		if (generateIndexBuffer(m_gridCellsX + 1, m_gridCellsY + 1) < 0)
			return;
		if (generateVertexBuffer(m_gridCellsX + 1, m_gridCellsY + 1,
				0x20, false) < 0)
			return;
	}
}
