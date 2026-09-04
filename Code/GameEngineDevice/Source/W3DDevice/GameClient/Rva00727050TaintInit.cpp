// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00727050: initialize the BFME taint/shroud cell buffers.

#include <string.h>

typedef float Real;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);

__forceinline Real bfmeFloatCeil27050(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline Real bfmeFloatFloor27050(Real value)
{
	return (Real)floor((double)value);
}

__forceinline long bfmeFloatToLong27050(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

void *__cdecl operator new[](unsigned int size);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_pad00[0xCA0];
	unsigned char m_taintAlpha;
	unsigned char m_padCA1[0xCF5 - 0xCA1];
	unsigned char m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	unsigned char m_pad00[8];
	int m_xExtent;
	int m_yExtent;
	int m_borderSize;
	unsigned char m_pad14[0x120E8 - 0x14];
	int m_drawWidth;
	int m_drawHeight;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/textureloader.h
class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned &width, unsigned &height);
};

#pragma comment(linker, "/alternatename:?Validate_Texture_Size@TextureLoader@@SAXAAI0@Z=?d_009056f0@@YAXXZ")

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class Rva00727050TaintFillThunk
{
public:
	void fill(unsigned char alpha);
};

#pragma comment(linker, "/alternatename:?fill@Rva00727050TaintFillThunk@@QAEXE@Z=?j_0002cfe3@@YAXXZ")

class Rva00727050TaintReAcquireThunk
{
public:
	void reacquire(void);
};

#pragma comment(linker, "/alternatename:?reacquire@Rva00727050TaintReAcquireThunk@@QAEXXZ=?j_000357d3@@YAXXZ")

class BfmeTaintManager
{
public:
	void resetGrid(void);
};

extern BfmeTaintManager *TheTaintManager;

#pragma comment(linker, "/alternatename:?resetGrid@BfmeTaintManager@@QAEXXZ=?m@Gen_00880e30@@QAEXXZ")

class Rva00727050TaintBuf
{
public:
	void init(WorldHeightMap *map, Real worldCellSizeX, Real worldCellSizeY);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	Real m_cellWidth;
	Real m_cellHeight;
	unsigned char *m_taintData;
	void *m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	unsigned char m_pad28[0x38 - 0x28];
	unsigned char *m_38;
	unsigned char *m_3c;
};

// ?init@Rva00727050TaintBuf@@QAEXPAVWorldHeightMap@@MM@Z
void Rva00727050TaintBuf::init(WorldHeightMap *map, Real worldCellSizeX,
	Real worldCellSizeY)
{
	int dstTextureWidth = 0;
	int dstTextureHeight = 0;
	m_cellWidth = worldCellSizeX;
	m_cellHeight = worldCellSizeY;

	if (map)
	{
		m_numCellsX = bfmeFloatToLong27050(bfmeFloatCeil27050(
			(Real)(map->m_xExtent - 1 - map->m_borderSize * 2)
				/ m_cellWidth * 10.0f));
		m_numCellsY = bfmeFloatToLong27050(bfmeFloatCeil27050(
			(Real)(map->m_yExtent - 1 - map->m_borderSize * 2)
				/ m_cellHeight * 10.0f));

		dstTextureWidth = m_numMaxVisibleCellsX =
			bfmeFloatToLong27050(bfmeFloatFloor27050(
				(Real)(map->m_drawWidth - 1) / m_cellWidth * 10.0f)) + 1;
		dstTextureHeight = m_numMaxVisibleCellsY =
			bfmeFloatToLong27050(bfmeFloatFloor27050(
				(Real)(map->m_drawHeight - 1) / m_cellHeight * 10.0f)) + 1;

		dstTextureWidth = m_numCellsX;
		dstTextureHeight = m_numCellsY;
		dstTextureWidth += 2;
		dstTextureHeight += 2;
		W3DRadarResetLock();
		TextureLoader::Validate_Texture_Size(
			(unsigned &)dstTextureWidth, (unsigned &)dstTextureHeight);
		W3DRadarResetUnlock();
	}

	m_38 = new unsigned char[*(volatile int *)&m_numCellsX * m_numCellsY];
	m_3c = new unsigned char[*(volatile int *)&m_numCellsX * m_numCellsY];
	memset(m_3c, 0x80, *(volatile int *)&m_numCellsX * m_numCellsY);
	memset(m_38, 0x80, *(volatile int *)&m_numCellsX * m_numCellsY);

	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn)
	{
		m_taintData = new unsigned char[*(volatile int *)&m_numCellsX * m_numCellsY * 4];
		memset(m_taintData, 0, *(volatile int *)&m_numCellsX * m_numCellsY * 4);
	}

	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn)
		reinterpret_cast<Rva00727050TaintFillThunk *>(this)->fill(
			TheWritableGlobalData->m_taintAlpha);

	if (dstTextureWidth != m_dstTextureWidth ||
		dstTextureHeight != m_dstTextureHeight)
	{
		if (m_dstTexture)
		{
			void *&dstTexture = m_dstTexture;
			if (dstTexture)
			{
				reinterpret_cast<TextureBaseClass *>(dstTexture)->Release_Ref();
				m_dstTexture = 0;
				TheWritableGlobalData;
			}
		}
	}

		if (!m_dstTexture)
		{
			m_dstTextureWidth = dstTextureWidth;
			m_dstTextureHeight = dstTextureHeight;
			reinterpret_cast<Rva00727050TaintReAcquireThunk *>(this)->reacquire();
		}

	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn &&
		TheTaintManager)
		reinterpret_cast<BfmeTaintManager *>(TheTaintManager)->resetGrid();
}
