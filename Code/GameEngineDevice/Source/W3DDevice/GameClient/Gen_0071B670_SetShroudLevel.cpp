// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?setShroudLevel@W3DShroud@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp
//
// Retail 0x0071B670. Update one BFME shroud cell and its terrain mirror.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
	unsigned char m_pad[0xc86];

public:
	UnsignedByte m_shroudAlpha;
};

extern GlobalData *TheWritableGlobalData;

class BaseHeightMapResetShroud
{
public:
	void setShroudLevel30BC(int x, int y, UnsignedByte level, bool immediate);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
private:
	unsigned char m_unmodelled_00[0x30b8];
	BaseHeightMapResetShroud *m_shroud;
	BaseHeightMapResetShroud *m_shroud30BC;

public:
	BaseHeightMapResetShroud *getShroud30BC() const
	{
		return m_shroud30BC;
	}
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class BfmeTaintManager
{
public:
	UnsignedByte getTaintLevelByte006e(int x, int y);
};

extern BfmeTaintManager *TheTaintManager;

unsigned int packShroudPixel(UnsignedByte level);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShroud.h
class W3DShroud
{
public:
	void setShroudLevel(int x, int y, UnsignedByte level, bool textureOnly);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	float m_cellWidth;
	float m_cellHeight;
	UnsignedShort *m_shroudData;
	void *m_dstTexture;
	void *m_20;
	void *m_24;
	int m_shroudFilter;
	float m_drawOriginX;             // positional, W3DShroud.h:119-122
	float m_drawOriginY;
	UnsignedByte m_drawFogOfWar;     // W3DShroud.cpp:104-107, the sibling destructor clears it after both fog arrays
	UnsignedByte m_clearDstTexture;
	// upstream spells this m_boderShroudLevel; the other W3DShroud TUs keep the
	// corrected name, so this one follows them
	UnsignedByte m_borderShroudLevel;
	UnsignedByte m_pad37;
	UnsignedByte *m_finalFogData;    // W3DShroud.cpp:317-318
	UnsignedByte *m_currentFogData;  // positional, W3DShroud.h:125-126
	// BFME-only: the fog interpolation at 0x0071B840 walks just m_dirty while this
	// is set and every cell otherwise; the ctor and 0x0071B770 both set it, so the
	// insert below is what keeps that walk complete
	UnsignedByte m_40;
	UnsignedByte m_pad41[3];
	_STL::set<int> m_dirty;
};

// ?setShroudLevel@W3DShroud@@QAEXHHE_N@Z
void W3DShroud::setShroudLevel(int x, int y, UnsignedByte level, bool textureOnly)
{
	if (m_shroudData == 0)
		return;

	if (x < m_numCellsX && y < m_numCellsY)
	{
		if (level < TheWritableGlobalData->m_shroudAlpha)
			level = TheWritableGlobalData->m_shroudAlpha;

		if (!textureOnly)
		{
			int cell = x + y * m_numCellsX;
			m_finalFogData[cell] = level;
			if (m_40)
				m_dirty.insert(cell);
		}

		m_shroudData[x + y * m_numCellsX] =
			(UnsignedShort)packShroudPixel(level);

		BaseHeightMapResetShroud *shroud30BC =
			TheTerrainRenderObject->getShroud30BC();
		if (shroud30BC && TheTaintManager)
		{
			shroud30BC->setShroudLevel30BC(
				x, y, TheTaintManager->getTaintLevelByte006e(x, y), true);
		}
	}
}
