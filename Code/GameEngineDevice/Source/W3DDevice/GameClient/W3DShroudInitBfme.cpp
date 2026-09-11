// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3DShroud::init.  The BFME WorldHeightMap moves the width, height,
// border, and draw extents relative to the Zero Hour header; keep both views
// local to this TU until the class identity is recovered from the image.

#include <string.h>

typedef float Real;
typedef unsigned char Bool;

extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);
extern "C" __declspec(dllimport) double __cdecl BfmeFloorER(double value);

__forceinline long Rva0071A150FloatToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

__forceinline Real Rva0071A150Ceil(Real value)
{
	return (Real)bfmeMathVE((double)value);
}

__forceinline Real Rva0071A150Floor(Real value)
{
	return (Real)BfmeFloorER((double)value);
}

void *__cdecl operator new[](unsigned int size);

class Rva0071A150WorldHeightMap
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

class TextureClass
{
public:
	void Release_Ref();
};

class Rva0071A150TexHandle
{
public:
	TextureClass *m_p;
};

__forceinline void Rva0071A150ReleaseTexture(TextureClass *&texture)
{
	if (texture)
	{
		texture->Release_Ref();
		texture = 0;
	}
}

class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned &width, unsigned &height);
};

#pragma comment(linker, "/alternatename:?Validate_Texture_Size@TextureLoader@@SAXAAI0@Z=?d_009056f0@@YAXXZ")

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class W3DShroud
{
public:
	Bool ReAcquireResources(void);
};

class PartitionManager
{
public:
	void notify(void);
};

#pragma comment(linker, "/alternatename:?notify@PartitionManager@@QAEXXZ=?m@Gen_008f7420@@QAEXXZ")

#define ThePartitionManager (*(PartitionManager **)0x012ED5BC)

class Rva0071A150W3DShroud
{
public:
	void init(Rva0071A150WorldHeightMap *map, Real worldCellSizeX,
		Real worldCellSizeY);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	Real m_cellWidth;
	Real m_cellHeight;
	unsigned short *m_shroudData;
	Rva0071A150TexHandle m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	int m_shroudFilter;
	Real m_drawOriginX;
	Real m_drawOriginY;
	unsigned char m_drawFogOfWar;
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;
	unsigned char m_pad37;
	unsigned char *m_finalFogData;
	unsigned char *m_currentFogData;
};

// ?init@W3DShroud@@QAEXPAVWorldHeightMap@@MM@Z
void Rva0071A150W3DShroud::init(Rva0071A150WorldHeightMap *map,
	Real worldCellSizeX, Real worldCellSizeY)
{
	int dstTextureWidth = 0;
	int dstTextureHeight = 0;
	m_cellWidth = worldCellSizeX;
	m_cellHeight = worldCellSizeY;

	if (map)
	{
		m_numCellsX = Rva0071A150FloatToLong(Rva0071A150Ceil(
			(Real)(map->m_xExtent - 1 - map->m_borderSize * 2)
				/ worldCellSizeX * *(const Real *)0x01075C74));
		m_numCellsY = Rva0071A150FloatToLong(Rva0071A150Ceil(
			(Real)(map->m_yExtent - 1 - map->m_borderSize * 2)
				/ m_cellHeight * *(const Real *)0x01075C74));

		dstTextureWidth = m_numMaxVisibleCellsX =
			Rva0071A150FloatToLong(Rva0071A150Floor(
				(Real)(map->m_drawWidth - 1) / m_cellWidth
					* *(const Real *)0x01075C74)) + 1;
		dstTextureHeight = m_numMaxVisibleCellsY =
			Rva0071A150FloatToLong(Rva0071A150Floor(
				(Real)(map->m_drawHeight - 1) / m_cellHeight
					* *(const Real *)0x01075C74)) + 1;

		dstTextureWidth = m_numCellsX + 2;
		dstTextureHeight = m_numCellsY + 2;
		W3DRadarResetLock();
// ?Validate_Texture_Size@TextureLoader@@QAEXXZ absent-from-retail
		TextureLoader::Validate_Texture_Size(
			(unsigned &)dstTextureWidth, (unsigned &)dstTextureHeight);
		bfmeUnlock1179();
	}

	m_finalFogData = new unsigned char[
		*(volatile int *)&m_numCellsX * m_numCellsY];
	m_currentFogData = new unsigned char[
		*(volatile int *)&m_numCellsX * m_numCellsY];
	memset(m_currentFogData, 0,
		*(volatile int *)&m_numCellsX * m_numCellsY);
	memset(m_finalFogData, 0,
		*(volatile int *)&m_numCellsX * m_numCellsY);

	m_shroudData = new unsigned short[
		*(volatile int *)&m_numCellsX * m_numCellsY];
	memset(m_shroudData, 0,
		*(volatile int *)&m_numCellsX * m_numCellsY * 2);

	if (dstTextureWidth != m_dstTextureWidth ||
		dstTextureHeight != m_dstTextureHeight)
	{
		if (m_dstTexture.m_p)
			Rva0071A150ReleaseTexture(m_dstTexture.m_p);
	}

	if (!m_dstTexture.m_p)
	{
		m_dstTextureWidth = dstTextureWidth;
		m_dstTextureHeight = dstTextureHeight;
		reinterpret_cast<W3DShroud *>(this)->ReAcquireResources();
	}
	if (ThePartitionManager)
		ThePartitionManager->notify();
}
