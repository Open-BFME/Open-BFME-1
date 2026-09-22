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

// Retail 0x006D5B10. The landed caller WorldHeightMap::rva0074C690 names it:
// it builds an Rva006D5280 texture and calls this through ILT 0x0002279B with
// the source tile array, the slot's first tile, its tile count and its cell
// width. The body is the 64-pixel-per-cell sibling of the flat update at
// 0x006D53A0 -- the same vertically flipped 1555 conversion, but reading the
// tiles straight out of the array instead of through WorldHeightMap, and with
// the cell extent fixed at 64 so MSVC unrolls the pixel loop four ways.
//
// The tile count is not read; the caller passes it and retail ignores it.
// The return type is Int, not the void the caller's own declaration uses:
// retail loads surface_desc.Height into EAX on the way out.

class Rva006D5280 : public TextureClass
{
public:
	Int update(TileData **tiles, Int firstTile, Int tileCount, Int cellWidth);
};

struct Rva006D5B10SurfaceStorage
{
	Rva006D53A0SurfaceDesc desc;
};

// ?update@Rva006D5280@@QAEHPAPAVTileData@@HHH@Z
Int Rva006D5280::update(TileData **tiles, Int firstTile, Int tileCount, Int cellWidth)
{
	SurfaceResource *surface_level;
	Rva006D5B10SurfaceStorage surface_storage;
	Rva006D53A0SurfaceDesc &surface_desc = surface_storage.desc;
	D3DLOCKED_RECT locked_rect;
	Rva006D5280 *self = this;
	BFME_DX8_ErrorCode(reinterpret_cast<BfmeD3DTexture *>(self->Peek_D3D_Base_Texture())->GetSurfaceLevel(0, &surface_level));
	BFME_DX8_ErrorCode(surface_level->GetDesc(&surface_desc));
	if (surface_desc.Width != cellWidth * TILE_PIXEL_EXTENT) {
		return 0;
	}

	BFME_DX8_ErrorCode(surface_level->LockRect(&locked_rect, NULL, 0));
	if (surface_desc.Format == D3DFMT_A1R5G5B5) {
		Int pixelBytes = 2;
		UnsignedByte *pBGRX_data = ((UnsignedByte *)locked_rect.pBits);
		Int cellX, cellY;
		for (cellX = 0; cellX < cellWidth; cellX++) {
			for (cellY = 0; cellY < cellWidth; cellY++) {
				UnsignedByte *pBGR = tiles[firstTile + cellY * cellWidth + cellX]->getDataPtr();
				if (pBGR == NULL) continue;
				Int k, l;
				for (k = TILE_PIXEL_EXTENT - 1; k >= 0; k--) {
					Short *pBGRX = (Short *)(pBGRX_data + (TILE_PIXEL_EXTENT * (cellWidth - cellY - 1) + k) * surface_desc.Width * pixelBytes + cellX * TILE_PIXEL_EXTENT * pixelBytes);
					for (l = 0; l < TILE_PIXEL_EXTENT; l++) {
						*pBGRX++ = 0x8000 + ((pBGR[2] >> 3) << 10) + ((pBGR[1] >> 3) << 5) + (pBGR[0] >> 3);
						pBGR += TILE_BYTES_PER_PIXEL;
					}
				}
			}
		}
	}

	surface_level->UnlockRect();
	surface_level->Release();
	BFME_DX8_ErrorCode(D3DXFilterTexture(reinterpret_cast<IDirect3DTexture8 *>(self->Peek_D3D_Base_Texture()), NULL, 0, 5));
	return surface_desc.Height;
}
