// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/TileData.h"
#include "WW3D2/dx8wrapper.h"
#include "d3dx8tex.h"

struct Rva006D53A0SurfaceDesc
{
	D3DFORMAT Format;
	D3DRESOURCETYPE Type;
	DWORD Usage;
	D3DPOOL Pool;
	UINT Size;
	UINT reserved;
	UINT Width;
	UINT Height;
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void __stdcall Release(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual int __stdcall GetDesc(Rva006D53A0SurfaceDesc *desc);
	virtual int __stdcall LockRect(D3DLOCKED_RECT *locked, const RECT *rect, unsigned flags);
	virtual int __stdcall UnlockRect(void);
};

class BfmeD3DTexture
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual int __stdcall GetSurfaceLevel(unsigned level, SurfaceResource **surface);
};

class BfmeMsgIBD
{
public:
	virtual BfmeMsgIBD *slot00(const void *value);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual BfmeMsgIBD *slot38(const void *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(int value);
};

class BfmeLogIBD
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual BfmeMsgIBD *slot6c(int first, int second);
};

extern BfmeLogIBD *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_DX8_ErrorCode(int result)
{
	if (result != 0)
	{
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->slot60();
		g_BFMEIndexBufferDebug->slot6c(0, 0)->slot38((const void *)0x111d770)
			->slot00((const void *)result)->slot4c(1);
	}
}

// Retail 0x006D5750. The 32-bit sibling of the landed 0x006D53A0 flat update:
// instead of writing 1555 pixels straight into a locked surface it stages the
// whole cellWidth*pixelsPerCell square in a heap X8R8G8B8 buffer, copies each
// tile row into it with memcpy, and hands the buffer to
// D3DXLoadSurfaceFromMemory. The caller and the texture vtable prove the ABI;
// nothing proves a semantic class name, so the address stays in it.
//

#include <string.h>

#pragma intrinsic(memcpy)

// TU-scoped: reference/shims/sweep/d3dx8tex.h routes to the validated DX8 shim,
// which declares D3DXFilterTexture but not the memory loader this body needs.
extern "C" HRESULT __stdcall D3DXLoadSurfaceFromMemory(void *pDestSurface,
	const void *pDestPalette, const void *pDestRect, const void *pSrcMemory,
	D3DFORMAT SrcFormat, unsigned SrcPitch, const void *pSrcPalette,
	const void *pSrcRect, unsigned long Filter, unsigned long ColorKey);

// The shim's D3DX_FILTER_BOX is 3; the SDK the retail build used numbers BOX 5,
// which is the value in the image.
#define RVA006D5750_FILTER_BOX 5

class Rva006D5750TextureClass : public TextureClass
{
public:
	Int Rva006D5750Update(WorldHeightMap *htMap, Int xCell, Int yCell,
		Int cellWidth, Int pixelsPerCell);
};

struct Rva006D5750SurfaceStorage
{
	Rva006D53A0SurfaceDesc desc;
};

// ?Rva006D5750Update@Rva006D5750TextureClass@@QAEHPAVWorldHeightMap@@HHHH@Z
Int Rva006D5750TextureClass::Rva006D5750Update(WorldHeightMap *htMap, Int xCell,
	Int yCell, Int cellWidth, Int pixelsPerCell)
{
	SurfaceResource *surface_level;
	Rva006D5750SurfaceStorage surface_storage;
	Rva006D53A0SurfaceDesc &surface_desc = surface_storage.desc;
	Rva006D5750TextureClass *self = this;
	Int width = cellWidth * pixelsPerCell;
	UnsignedByte *buffer = (UnsignedByte *)(new UnsignedInt[width * width]);
	Int cellStride = pixelsPerCell * 4;

	Int cellX, cellY;
	for (cellX = 0; cellX < cellWidth; cellX++) {
		for (cellY = 0; cellY < cellWidth; cellY++) {
			UnsignedByte *pBGR = htMap->getPointerToTileData(xCell + cellX, yCell + cellY, pixelsPerCell);
			if (pBGR == NULL) continue;
			Int k;
			for (k = pixelsPerCell - 1; k >= 0; k--) {
				UnsignedByte *pBGRX = buffer + (cellWidth - cellY - 1) * cellStride * width +
					k * width * 4 + cellX * cellStride;
				memcpy(pBGRX, pBGR, pixelsPerCell * 4);
				pBGR += pixelsPerCell * TILE_BYTES_PER_PIXEL;
			}
		}
	}

	BFME_DX8_ErrorCode(reinterpret_cast<BfmeD3DTexture *>(self->Peek_D3D_Base_Texture())->GetSurfaceLevel(0, &surface_level));
	BFME_DX8_ErrorCode(surface_level->GetDesc(&surface_desc));
	if (surface_desc.Width != width) {
		delete [] buffer;
		return 0;
	}

	RECT source_rect;
	source_rect.top = 0;
	source_rect.left = 0;
	source_rect.bottom = width;
	source_rect.right = width;
	BFME_DX8_ErrorCode(D3DXLoadSurfaceFromMemory(surface_level, NULL, NULL,
		buffer, D3DFMT_X8R8G8B8, width * 4, NULL, &source_rect, D3DX_FILTER_NONE, 0));
	surface_level->Release();
	BFME_DX8_ErrorCode(D3DXFilterTexture(reinterpret_cast<IDirect3DTexture8 *>(self->Peek_D3D_Base_Texture()), NULL, 0, RVA006D5750_FILTER_BOX));
	delete [] buffer;
	return width;
}
