// ?render@W3DShroud@@QAEXPAVCameraClass@@@Z
// Retail 0x0071BBC0 (572 bytes): BFME W3DShroud::render.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/GameEngine/Include /Igame/GameEngine/Source /Igame/Libraries/Include /Igame/Libraries/Source /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngineDevice/Include /Igame/GameEngineDevice/Source /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Main
// BFME W3DShroud::render, retail 0x0071BBC0.
//
// The BFME shroud stores packed 16-bit cells directly and copies the full
// logical grid into the reset texture.  Its render body is therefore not the
// Zero Hour source body: the source texture and DX8 rectangle-copy path are
// absent.  The object layout is witnessed by W3DShroudBfme.cpp, while the
// terrain-map offsets are witnessed by WorldHeightMap.cpp and the retail
// loads in this body.

#include "../../../../../inputs/reference/shims/d3d8_shim_validated.h"

#include <string.h>

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) double __cdecl floor(double value);

extern const float g_bfmeDirectionWeight1285;

class CameraClass;

class TextureBaseClass;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8(void)
	{
		return D3DDevice;
	}

private:
	static IDirect3DDevice8 *D3DDevice;
};

// The BFME SurfaceClass rectangle-lock overload is absent from the header.
class SurfaceClass
{
public:
	void *Lock(int *pitch, int left, int top, int right, int bottom);
	void Unlock(void);
};

class ShroudFilter
{
public:
	int getMagFilter(void) const { return m_filter4; }
	void setMagFilter(int filter) { m_filter4 = filter; }
	void setMinFilter(int filter) { m_filter0 = filter; }
	int m_filter0;
	int m_filter4;
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
	int getBorderSize(void) const { return m_borderSize; }
	int getDrawOriginX(void) const { return m_drawOriginX; }
	int getDrawOriginY(void) const { return m_drawOriginY; }
	int getDrawWidth(void) const { return m_drawWidth; }
	int getDrawHeight(void) const { return m_drawHeight; }
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

	ShroudTexture *texture =
		reinterpret_cast<ShroudTexture *>(&m_dstTexture);
	if (!texture->m_p)
		return;

	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	if (device && device->TestCooperativeLevel() != D3D_OK)
		return;

	WorldHeightMap *hm = TheTerrainRenderObject->getMap();
	int visStartX = BfmeFloatToLong(BfmeFloor(
		(float)(hm->getDrawOriginX() - hm->getBorderSize()) /
		m_cellWidth * g_bfmeDirectionWeight1285));
	int visStartY = BfmeFloatToLong(BfmeFloor(
		(float)(hm->getDrawOriginY() - hm->getBorderSize()) /
		m_cellHeight * g_bfmeDirectionWeight1285));
	int visEndX = BfmeFloatToLong(BfmeFloor(
		(float)(hm->getDrawWidth() - 1) /
		m_cellWidth * g_bfmeDirectionWeight1285));
	int visEndY = BfmeFloatToLong(BfmeFloor(
		(float)(hm->getDrawHeight() - 1) /
		m_cellHeight * g_bfmeDirectionWeight1285));
	(void)visStartX;
	(void)visStartY;
	visEndX = m_numCellsX;
	visEndY = m_numCellsY;

	m_drawOriginX = m_cellWidth * 0.0f;
	m_drawOriginY = m_cellHeight * 0.0f;

	if (texture->getFilter()->getMagFilter() != m_shroudFilter)
	{
		texture->getFilter()->setMagFilter(m_shroudFilter);
		texture->getFilter()->setMinFilter(m_shroudFilter);
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

	{
		UnsignedShort *src = m_shroudData;
		int pitch;
		UnsignedShort *dst = (UnsignedShort *)
			reinterpret_cast<SurfaceClass *>(&surface)->Lock(
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

		reinterpret_cast<SurfaceClass *>(&surface)->Unlock();
	}
}
