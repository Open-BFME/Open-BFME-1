// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x006D2280, 215 bytes.  The HeightMapRenderObjClass vtable at
// 0x0111DC88 (installed by the matched constructor at 0x006D1C80) reaches
// this body through ILT 0x00012ADF in slot 138, right after the matched
// doPartialUpdate in slot 137.  The Zero Hour order would make it
// staticLightingChanged, but BFME's slot list carries extra entries and this
// override takes a one-byte flag, so it keeps the address token.
//
// It forwards the flag to the 0x006C8DA0 base body, then (with a height map
// at +0x2FF4) walks every 0xC4-byte W3DTerrainBackground tile at +0x30D8,
// yielding with Sleep(0) per tile: with the flag set the tile rebuilds over
// the whole map through the 0x0072D210 body, otherwise it resets its
// buffers.  Finally it clears the +0x3174 update-state byte.

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

extern void j_0003871c();
extern void j_000324d4();
extern void j_0002ad3d();

class WorldHeightMap;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class W3DTerrainBackground
{
public:
	char m_pad[0xc4];
};

class HeightMapRenderObjClass
{
public:
	virtual void rva006D2280(bool flag);

private:
	char pad004[0x2ff4 - 0x04];
	WorldHeightMap *m_map;
	char pad2ff8[0x3014 - 0x2ff8];
	unsigned char byte_3014;
	char pad3015[0x30d8 - 0x3015];
	W3DTerrainBackground *m_tiles;
	char pad30dc[0x30e0 - 0x30dc];
	int m_tilesWidth;
	int m_tilesHeight;
	char pad30e8[0x3174 - 0x30e8];
	unsigned char byte_3174;
};

void HeightMapRenderObjClass::rva006D2280(bool flag)
{
	typedef void (HeightMapRenderObjClass::*BaseFn)(bool);
	typedef void (W3DTerrainBackground::*UpdateFn)(const IRegion2D &, WorldHeightMap *, bool, unsigned char);
	typedef void (W3DTerrainBackground::*ResetFn)();

	union { void (__cdecl *freeFunction)(); BaseFn memberFunction; } callBase;
	callBase.freeFunction = ::j_0003871c;
	(this->*callBase.memberFunction)(flag);

	if (m_map == 0)
		return;

	IRegion2D bounds;
	bounds.lo.x = 0;
	bounds.lo.y = 0;
	bounds.hi.x = m_tilesWidth * 16;
	bounds.hi.y = m_tilesHeight * 16;

	union { void (__cdecl *freeFunction)(); UpdateFn memberFunction; } callUpdate;
	callUpdate.freeFunction = ::j_000324d4;
	union { void (__cdecl *freeFunction)(); ResetFn memberFunction; } callReset;
	callReset.freeFunction = ::j_0002ad3d;

	for (int i = 0; i < m_tilesWidth; i++)
	{
		for (int j = 0; j < m_tilesHeight; j++)
		{
			W3DTerrainBackground *tile = m_tiles + j * m_tilesWidth + i;
			Sleep(0);
			if (flag)
				(tile->*callUpdate.memberFunction)(bounds, m_map, false, byte_3014);
			else
				(tile->*callReset.memberFunction)();
		}
	}
	byte_3174 = 0;
}
