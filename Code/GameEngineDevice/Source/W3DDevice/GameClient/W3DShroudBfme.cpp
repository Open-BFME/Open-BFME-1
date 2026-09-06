// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0W3DShroud@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp
// readable body of ??1W3DShroud@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp
// readable body of ?ReAcquireResources@W3DShroud@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp
// readable body of ?setShroudLevel@W3DShroud@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp
//
// The four BFME W3DShroud bodies that own the object's storage: construction
// (retail 0x0071B590), teardown (0x0071B3D0), device-resource reacquisition
// (0x00719FB0) and the per-cell update (0x0071B670). They had four copies of
// the class between them and each copy could only see the fields its own body
// touched, so no one file said what the 0x44-byte header actually is. It says
// it once here.
//
// Two fields gain their names from that: the constructor could only call
// +0x20 and +0x24 m_20 and m_24 because it zeroes them, while
// ReAcquireResources passes exactly those two to the texture init as its width
// and height. The reverse holds for the fog arrays at +0x38/+0x3c, which the
// destructor could only free -- setShroudLevel indexes the first of them by
// cell, and that is what names it.
//
// _BFME_RETAIL_TREE_INSERT_LAYOUT selects the retail STLport's insert_unique
// shape, which is what setShroudLevel's m_dirty.insert has to emit; the
// constructor only default-constructs the set and the destructor only tears it
// down, so neither is affected by it.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

typedef unsigned char Bool;
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

struct IDirect3DBaseTexture8;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class TexHandle
{
public:
	TexHandle() : m_p(0) {}
	~TexHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}
	void Clear()
	{
		if (m_p)
		{
			m_p->Release_Ref();
			m_p = 0;
		}
	}
	TextureBaseClass *m_p;
};

class ShroudFilter
{
public:
	char m_pad00[0x0c];
	int m_uAddress;
	int m_vAddress;
	void setMipMapping(int mode);
};

// The same four bytes as TexHandle, reached through the name that carries the
// retail pin for getFilter(); ReAcquireResources already views the handle
// through three different classes for the three entry points it calls on it.
class ShroudTexture
{
public:
	ShroudFilter *getFilter();

	TextureBaseClass *m_p;
};

class Rva006D6050
{
public:
	void init(int width, int height, int format, int mipLevels, int pool, int renderTarget);
};

class Gen_00920a60
{
public:
	void m(int value);
};

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

void operator delete[](void *);

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
	W3DShroud();
	~W3DShroud();
	Bool ReAcquireResources(void);
	void setShroudLevel(int x, int y, UnsignedByte level, bool textureOnly);

private:
	int m_numCellsX;                    // +0x00
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	float m_cellWidth;                  // +0x10, 10.0f in BFME
	float m_cellHeight;
	UnsignedShort *m_shroudData;        // +0x18, one packed pixel per cell
	TexHandle m_dstTexture;             // +0x1c
	int m_dstTextureWidth;              // +0x20, the two extents ReAcquireResources
	int m_dstTextureHeight;             // +0x24   hands to the texture init
	int m_shroudFilter;                 // +0x28
	float m_drawOriginX;                // +0x2c, positional, W3DShroud.h:119-122
	float m_drawOriginY;
	UnsignedByte m_drawFogOfWar;        // +0x34, W3DShroud.cpp:104-107; the
	UnsignedByte m_clearDstTexture;     //   destructor clears it after both arrays
	// upstream spells this m_boderShroudLevel; the corrected name is what the
	// W3DShroud TUs have always used here
	UnsignedByte m_borderShroudLevel;   // +0x36
	UnsignedByte m_pad37;
	UnsignedByte *m_finalFogData;       // +0x38, indexed by cell in setShroudLevel
	UnsignedByte *m_currentFogData;     // +0x3c, positional, W3DShroud.h:125-126
	// BFME-only: the fog interpolation at 0x0071B840 walks just m_dirty while
	// this is set and every cell otherwise, so setShroudLevel's insert is what
	// keeps that walk complete. The constructor and 0x0071B770 both set it.
	UnsignedByte m_40;
	UnsignedByte m_pad41[3];
	_STL::set<int> m_dirty;             // +0x44
};

// ??0W3DShroud@@QAE@XZ
W3DShroud::W3DShroud()
	: m_numCellsX(0)
	, m_numCellsY(0)
	, m_numMaxVisibleCellsX(0)
	, m_numMaxVisibleCellsY(0)
	, m_cellWidth(10.0f)
	, m_cellHeight(10.0f)
	, m_shroudData(0)
	, m_dstTextureWidth(0)
	, m_dstTextureHeight(0)
	, m_shroudFilter(4)
	, m_drawOriginX(0)
	, m_drawOriginY(0)
	, m_drawFogOfWar(0)
	, m_clearDstTexture(1)
	, m_borderShroudLevel(TheWritableGlobalData->m_shroudAlpha)
	, m_finalFogData(0)
	, m_currentFogData(0)
	, m_40(1)
{
}

// ??1W3DShroud@@QAE@XZ
W3DShroud::~W3DShroud()
{
	if (m_dstTexture.m_p)
		m_dstTexture.Clear();
	if (m_shroudData)
		operator delete[](m_shroudData);
	m_shroudData = 0;
	if (m_finalFogData)
		operator delete[](m_finalFogData);
	m_finalFogData = 0;
	if (m_currentFogData)
		operator delete[](m_currentFogData);
	m_currentFogData = 0;
	m_drawFogOfWar = 0;
}

// ?ReAcquireResources@W3DShroud@@QAEEXZ
Bool W3DShroud::ReAcquireResources(void)
{
	if (!m_dstTextureWidth)
		return 1;

	W3DRadarResetLock();

	reinterpret_cast<Rva006D6050 *>(&m_dstTexture)->init(
		m_dstTextureWidth, m_dstTextureHeight, 0x1a, 1, 1, 0);
	if (!reinterpret_cast<TextureBaseClass *>(&m_dstTexture)->Peek_D3D_Base_Texture())
	{
		if (m_dstTexture.m_p)
		{
			m_dstTexture.m_p->Release_Ref();
			m_dstTexture.m_p = 0;
		}
		m_dstTextureWidth = 0;
		m_dstTextureHeight = 0;
		return 0;
	}

	reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->m_uAddress = 1;
	reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->m_vAddress = 1;
	reinterpret_cast<Gen_00920a60 *>(
		reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter())->m(0);
	m_clearDstTexture = 1;
	W3DRadarResetUnlock();
	return 1;
}

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
