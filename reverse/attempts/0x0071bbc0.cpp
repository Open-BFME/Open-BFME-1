// ?render@W3DShroud@@QAEXPAVCameraClass@@@Z
// partial score=0.69 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /ICode/GameEngine/Include /ICode/GameEngine/Source /ICode/Libraries/Include /ICode/Libraries/Source /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngineDevice/Include /ICode/GameEngineDevice/Source /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Main
// BFME W3DShroud::render, retail 0x0071BBC0.
//
// The BFME shroud stores packed 16-bit cells directly and copies the full
// logical grid into the reset texture.  Its render body is therefore not the
// Zero Hour source body: the source texture and DX8 rectangle-copy path are
// absent.  The object layout is witnessed by W3DShroudBfme.cpp, while the
// terrain-map offsets are witnessed by WorldHeightMap.cpp and the retail
// loads in this body.

#include "../../../../../reference/shims/dx8state/DX8State.h"

#include <string.h>

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) double __cdecl floor(double value);

extern const float BfmeZeroRange;
extern const float g_bfmeDirectionWeight1285;

class CameraClass;

// The BFME SurfaceClass rectangle-lock overload is a real retail method, but
// the canonical WW3D header only declares the full-surface Lock(int*) form.
// Keep the canonical DX8 header as the source of the class declaration and
// route this ABI view to the already matched overload without redeclaring the
// class in this TU.
class Rva0090C710SurfaceLockView
{
public:
	void *Lock(int *pitch, int left, int top, int right, int bottom);
	void Unlock(void);
};

#pragma comment(linker, "/alternatename:?Lock@Rva0090C710SurfaceLockView@@QAEPAXPAHHHHH@Z=?Lock@SurfaceClass@@QAEPAXPAHHHHH@Z")
#pragma comment(linker, "/alternatename:?Unlock@Rva0090C710SurfaceLockView@@QAEXXZ=?Unlock@SurfaceClass@@QAEXXZ")

class ShroudFilter
{
public:
	int m_minFilter;
	int m_magFilter;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	TextureBaseClass *m_p;
};

class TexHandle
{
public:
	TextureBaseClass *m_p;
};

class W3DRadarResetSurface
{
public:
	IDirect3DSurface8 *m_surface;
	~W3DRadarResetSurface(void);
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel(void);
};

class WorldHeightMap
{
public:
	unsigned char m_head[0x10];
	int m_borderSize;
	unsigned char m_between[0x120e0 - 0x14];
	int m_drawOriginX;
	int m_drawOriginY;
	int m_drawWidth;
	int m_drawHeight;
};

class BaseHeightMapRenderObjClass
{
public:
	unsigned char m_head[0x2ff4];
	WorldHeightMap *m_map;

	WorldHeightMap *getMap(void) const
	{
		return m_map;
	}
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// These are the two BFME call-site contracts used by the retail body.  The
// thunks preserve the image's ILT-mediated calls while the source names retain
// the ZH W3DShroud ownership established by the reference class.
class W3DShroud;

#pragma comment(linker, "/alternatename:?interpolateFogLevels@W3DShroud@@IAEXPAUtagRECT@@@Z=?j_0001494d@@YAXXZ")
#pragma comment(linker, "/alternatename:?fillBorderShroudData@W3DShroud@@IAEXEPAVSurfaceClass@@@Z=?j_00045c46@@YAXXZ")

class W3DShroud
{
public:
	void render(CameraClass *cam);

protected:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	float m_cellWidth;
	float m_cellHeight;
	UnsignedShort *m_shroudData;
	TexHandle m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	int m_shroudFilter;
	float m_drawOriginX;
	float m_drawOriginY;
	UnsignedByte m_drawFogOfWar;
	UnsignedByte m_clearDstTexture;
	UnsignedByte m_borderShroudLevel;
	UnsignedByte m_pad37;
	UnsignedByte *m_finalFogData;
	UnsignedByte *m_currentFogData;
	UnsignedByte m_40;

	void interpolateFogLevels(RECT *rect);
	void fillBorderShroudData(UnsignedByte level, SurfaceClass *surface);
};

static __forceinline long BfmeFloatToLong(float value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

static __forceinline float BfmeFloor(float value)
{
	return (float)floor((double)value);
}

void W3DShroud::render(CameraClass *cam)
{
	(void)cam;

	if (!m_shroudData)
		return;

	if (!m_dstTexture.m_p)
		return;

	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	if (device && device->TestCooperativeLevel() != D3D_OK)
		return;

	WorldHeightMap *hm = TheTerrainRenderObject->getMap();
	int visStartX = BfmeFloatToLong(BfmeFloor(
		(float)(hm->m_drawOriginX - hm->m_borderSize) /
		m_cellWidth * g_bfmeDirectionWeight1285));
	int visStartY = BfmeFloatToLong(BfmeFloor(
		(float)(hm->m_drawOriginY - hm->m_borderSize) /
		m_cellHeight * g_bfmeDirectionWeight1285));
	int visEndX = BfmeFloatToLong(BfmeFloor(
		(float)(hm->m_drawWidth - 1) /
		m_cellWidth * g_bfmeDirectionWeight1285));
	int visEndY = BfmeFloatToLong(BfmeFloor(
		(float)(hm->m_drawHeight - 1) /
		m_cellHeight * g_bfmeDirectionWeight1285));
	(void)visStartX;
	(void)visStartY;
	visEndX = m_numCellsX;
	visEndY = m_numCellsY;

	m_drawOriginX = BfmeZeroRange * m_cellWidth;
	m_drawOriginY = BfmeZeroRange * m_cellHeight;

	ShroudFilter *filter =
		reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter();
	if (filter->m_magFilter != m_shroudFilter)
	{
		reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->m_magFilter =
			m_shroudFilter;
	reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->m_minFilter =
		m_shroudFilter;
	}

	W3DRadarResetSurface surface =
		reinterpret_cast<W3DRadarResetTexture *>(&m_dstTexture)->getSurfaceLevel();

	RECT srcRect;
	interpolateFogLevels(&srcRect);

	if (m_clearDstTexture)
	{
		m_clearDstTexture = 0;
		fillBorderShroudData(m_borderShroudLevel,
			reinterpret_cast<SurfaceClass *>(&surface));
	}

	UnsignedShort *src = m_shroudData;
	int pitch;
	UnsignedShort *dst = (UnsignedShort *)
		reinterpret_cast<Rva0090C710SurfaceLockView *>(&surface)->Lock(
		&pitch, 1, 1, visEndX + 1, visEndY + 1);

	if (visEndY > 0)
	{
		int row_bytes = visEndX * (int)sizeof(UnsignedShort);
		for (int y = 0; y < visEndY; ++y)
		{
			memcpy(dst, src, row_bytes);
			dst = (UnsignedShort *)((char *)dst + pitch);
			src += m_numCellsX;
		}
	}

	reinterpret_cast<Rva0090C710SurfaceLockView *>(&surface)->Unlock();
}
