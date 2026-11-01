// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail RVA 0x006D1D80, 416 bytes. HeightMapRenderObjClass vtable
// 0x0111DC88 slot 137 routes through 0x0002E087; the landed constructor
// at 0x006D1C80 installs that table. Preserves the banked method identity.
// This BFME body differs from the ZH vertex update: it visits 0xC4-byte tiles.
// The map replacement is conditional on pMap; X is the outer loop.
// The range is forwarded by reference and the original pMap is passed again.
// Four tile bounds form one IRegion2D, preserving retail's stack allocation.
// Native fast_float2long_round supplies the proven x87 FLD/FISTP conversion;
// ordinary C++ casts emit __ftol2 and do not implement that instruction shape.

#include "basetype.h"

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

// Former COFF reference ?g_rva006D1D80Scale@@3MB: retail 0x0109DF58 is
// __real@3d800000 (0.0625f), checked through the literal operands below.

extern "C" void __cdecl __identifier("?d_0072d210@@YAXXZ")();
class WorldHeightMap
{
public:
	virtual void release(void);			///< vtable slot 0, thiscall no-args
};

struct Rva0072E150Region
{
	Int loX, loY, hiX, hiY;
};

class W3DTerrainBackground
{
public:
	void setFlip(WorldHeightMap *map);
	// retail body is still the gen-dump row ?d_0072d210@@YAXXZ (no C++ row yet); call it by that defined name

	char m_body[0xC4];
};

// Static (internal linkage): an inline member here would emit a COMDAT copy of
// the pinned member name that retail-truth judges wrong (5-byte jmp vs the
// 1920-byte body). The static forwarder inlines to a direct call instead.
static __forceinline void Rva0072D210Forward(W3DTerrainBackground *tile, const Rva0072E150Region &a0, WorldHeightMap *a1, Bool a2, Bool a3) {
	 union { void (__cdecl *symbol)(); void (W3DTerrainBackground::*member)(const Rva0072E150Region &,WorldHeightMap *,Bool,Bool); } c;
	 c.symbol = &__identifier("?d_0072d210@@YAXXZ");
	 (tile->*c.member)(a0,a1,a2,a3);
}

class RenderObjClass;				///< opaque; only used for the template ABI name below

template <class T> class RefMultiListIterator;	///< opaque; only used for typed pointer ABI

class HeightMapRenderObjClass
{
public:
	virtual void doPartialUpdate(const IRegion2D &partialRange,
		WorldHeightMap *pMap,
		RefMultiListIterator<RenderObjClass> *pDirtyRenderObjectClasses);

private:
	char m_bfmeHead[0x2ff4 - 0x04];
	WorldHeightMap *m_map;					///< retail this+0x2ff4
	char m_bfmeGap2ff8[0x3014 - 0x2ff8];
	Bool m_bfme3014;					///< retail this+0x3014
	char m_bfmeGap3015[0x30d4 - 0x3015];
	short *m_bfmeIndices;					///< retail this+0x30d4
	W3DTerrainBackground *m_tiles;				///< retail this+0x30d8
	Int m_bfme30dc;						///< retail this+0x30dc
	Int m_mapWidth;						///< retail this+0x30e0
	Int m_mapHeight;					///< retail this+0x30e4
	char m_bfmeGap30e8[0x3174 - 0x30e8];
	Bool m_bfme3174;					///< retail this+0x3174
};

void HeightMapRenderObjClass::doPartialUpdate(const IRegion2D &partialRange,
	WorldHeightMap *pMap, RefMultiListIterator<RenderObjClass> *pDirtyRenderObjectClasses)
{
	if (pMap)
	{
		++*(Int *)((char *)pMap + 4);

		WorldHeightMap *oldMap = m_map;
		if (oldMap)
		{
			if (--*(Int *)((char *)oldMap + 4) == 0)
				oldMap->release();
		}
		m_map = pMap;
	}

	IRegion2D tileRange;
	float scaledLoX = (float)partialRange.lo.x * 0.0625f;
	float floorLoX = (float)floor((double)scaledLoX);
	tileRange.lo.x = fast_float2long_round(floorLoX);

	float scaledLoY = (float)partialRange.lo.y * 0.0625f;
	float floorLoY = (float)floor((double)scaledLoY);
	tileRange.lo.y = fast_float2long_round(floorLoY);

	float scaledHiX = (float)partialRange.hi.x * 0.0625f;
	float ceilHiX = (float)ceil((double)scaledHiX);
	tileRange.hi.x = fast_float2long_round(ceilHiX);

	float scaledHiY = (float)partialRange.hi.y * 0.0625f;
	float ceilHiY = (float)ceil((double)scaledHiY);
	tileRange.hi.y = fast_float2long_round(ceilHiY);

	if (tileRange.lo.x < 0)
		tileRange.lo.x = 0;
	if (tileRange.lo.y < 0)
		tileRange.lo.y = 0;
	if (tileRange.hi.x >= m_mapWidth)
		tileRange.hi.x = m_mapWidth;
	if (tileRange.hi.y >= m_mapHeight)
		tileRange.hi.y = m_mapHeight;

	for (Int x = tileRange.lo.x; x < tileRange.hi.x; ++x)
		for (Int y = tileRange.lo.y; y < tileRange.hi.y; ++y)
		{
			W3DTerrainBackground *tile = &m_tiles[y * m_mapWidth + x];
			tile->setFlip(pMap);
			Rva0072D210Forward(tile,
				reinterpret_cast<const Rva0072E150Region &>(partialRange),
				pMap, true, m_bfme3014);
		}

	m_bfme3174 = false;
}
