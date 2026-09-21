// ?doPartialUpdate@HeightMapRenderObjClass@@UAEXABUIRegion2D@@PAVWorldHeightMap@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// partial score=0.35 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// readable body of ?doPartialUpdate@HeightMapRenderObjClass@@UAEXABUIRegion2D@@PAVWorldHeightMap@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
//
// Identity proven by an earlier attempt via vtable slot 137 and the
// +0x2FF4 map / +0x30D8 tile-array layout this file's sibling
// (HeightMapRenderObjClass_freeMapResources.cpp) already established for
// +0x30D4/+0x30D8/+0x30DC/+0x30E0/+0x30E4. That attempt reached 202/416
// bytes different from a "conversion-local-stack-layout" mismatch across
// the four floor/ceil tile-index conversions; this is a fresh attempt at
// the same body with the same known blocker up front.
//
// Behaviour: swaps in the new WorldHeightMap (ref-counted: AddRef the new
// one, Release+delete-if-zero the old one via its own vtable slot 0), then
// converts the incoming IRegion2D (four ints, lo/hi) into map tile indices
// via BfmeFloorER (lo) and bfmeMathVE (hi, a ceil-shaped sibling import
// already used the same way elsewhere), clamps them to [0,width)/[0,height),
// and walks the resulting rectangle of W3DTerrainBackground tiles (stride
// 0xC4, base at this+0x30D8, this+0x30E0 wide) calling each tile's
// setFlip(WorldHeightMap*) then its four-argument update method (pinned
// address-derived, ?rva0072D210@W3DTerrainBackground@@...; the pin's own
// second-parameter type name is a guess, the real argument here is the
// dirty-object iterator this function receives, forwarded unchanged and
// only needed for correct mangling/ABI). Finishes by clearing a flag at
// this+0x3174.
//
// callees, in body order (all already matched/pinned):
//   ?setFlip@W3DTerrainBackground@@QAEXPAVWorldHeightMap@@@Z ILT 0x00047668 -> 0x00729F00
//   ?rva0072D210@W3DTerrainBackground@@QAEXABURva0072E150Region@@PAVWorldHeightMap@@_N2@Z
//     ILT 0x000324D4 -> 0x0072D210 (address-derived pin; ret 0x10)
//   __imp__BfmeFloorER (0x00F593B8), __imp__bfmeMathVE (0x00F59394)
//
// globals: a float scale constant at 0x0109DF58

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl BfmeFloorER(double value);
extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);

extern const float g_rva006D1D80Scale;			///< retail [0x0109DF58]

struct IRegion2D
{
	Int loX, loY, hiX, hiY;
};

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
	void rva0072D210(const Rva0072E150Region &region, WorldHeightMap *dirty,
		Bool a, Bool b);

	char m_body[0xC4];
};

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
		++*(Int *)((char *)pMap + 4);

	WorldHeightMap *oldMap = m_map;
	if (oldMap)
	{
		if (--*(Int *)((char *)oldMap + 4) == 0)
			oldMap->release();
	}
	m_map = pMap;

	float scaledLoX = (float)partialRange.loX * g_rva006D1D80Scale;
	float floorLoX = (float)BfmeFloorER((double)scaledLoX);
	Int minTileX = (Int)floorLoX;

	float scaledLoY = (float)partialRange.loY * g_rva006D1D80Scale;
	float floorLoY = (float)BfmeFloorER((double)scaledLoY);
	Int minTileY = (Int)floorLoY;

	float scaledHiX = (float)partialRange.hiX * g_rva006D1D80Scale;
	float ceilHiX = (float)bfmeMathVE((double)scaledHiX);
	Int maxTileX = (Int)ceilHiX;

	float scaledHiY = (float)partialRange.hiY * g_rva006D1D80Scale;
	float ceilHiY = (float)bfmeMathVE((double)scaledHiY);
	Int maxTileY = (Int)ceilHiY;

	if (minTileX < 0)
		minTileX = 0;
	if (minTileY < 0)
		minTileY = 0;
	if (maxTileX > m_mapWidth)
		maxTileX = m_mapWidth;
	if (maxTileY > m_mapHeight)
		maxTileY = m_mapHeight;

	if (minTileY < maxTileY)
	{
		Int y = minTileY;
		do
		{
			if (minTileX < maxTileX)
			{
				Int x = minTileX;
				do
				{
					W3DTerrainBackground *tile =
						(W3DTerrainBackground *)((char *)m_tiles +
						(y * m_mapWidth + x) * 0xC4);

					tile->setFlip(pMap);

					Rva0072E150Region forwarded;
					forwarded.loX = partialRange.loX;
					forwarded.loY = partialRange.loY;
					forwarded.hiX = partialRange.hiX;
					forwarded.hiY = partialRange.hiY;
					tile->rva0072D210(forwarded,
						(WorldHeightMap *)pDirtyRenderObjectClasses,
						true, m_bfme3014);

					++x;
				} while (x < maxTileX);
			}

			++y;
		} while (y < maxTileY);
	}

	m_bfme3174 = false;
}
