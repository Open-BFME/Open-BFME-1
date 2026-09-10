// ?bfmeAllocateCells@PathfindLayer@@QAEXPBUIRegion2D@@@Z
// partial score=0.94 date=2026-09-10
// cl: /O2 /DNDEBUG /MD /EHsc
// BFME PathfindLayer::allocateCells (retail 0x003FBED0). No m_bridge falls
// back to a PolygonTrigger chain bounding box via the same getBounds slot,
// whose out param is really an IRegion2D (ICF-folded onto Bridge's name).

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

extern "C" float g_bfmeScaleBK;

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct Coord2D { Real x, y; };
struct ICoord2D { Int x, y; };

struct Region2D { Coord2D lo, hi; };
struct IRegion2D { ICoord2D lo, hi; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Terrain/Bridge.h
class Bridge
{
public:
	void getBounds(Region2D *bounds) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	PolygonTrigger *getNext(void) const { return m_next; }
private:
	char m_bfmeHead[4];
	PolygonTrigger *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	PathfindCell();
	~PathfindCell();
private:
	unsigned char m_opaque[0x10];
};
typedef PathfindCell *PathfindCellP;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	void bfmeAllocateCells(const IRegion2D *extent);

private:
	PathfindCell *m_blockOfMapCells;
	PathfindCellP *m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	unsigned char m_middle[0x38 - 0x18];
	Bridge *m_bridge;
	PolygonTrigger *m_trigger;
};

// ?bfmeAllocateCells@PathfindLayer@@QAEXPBUIRegion2D@@@Z
void PathfindLayer::bfmeAllocateCells(const IRegion2D *extent)
{
	if (m_blockOfMapCells != 0)
		return;

	Region2D bridgeBounds;
	if (m_bridge != 0) {
		bridgeBounds = *(Region2D *)((char *)m_bridge + 0x78);
	} else if (m_trigger != 0) {
		IRegion2D rawBounds;
		((Bridge *)m_trigger)->getBounds((Region2D *)&rawBounds);
		bridgeBounds.lo.x = (Real)rawBounds.lo.x;
		bridgeBounds.hi.x = (Real)rawBounds.hi.x;
		bridgeBounds.lo.y = (Real)rawBounds.lo.y;
		bridgeBounds.hi.y = (Real)rawBounds.hi.y;
		PolygonTrigger *trigger = m_trigger->getNext();
		if (trigger != 0) {
			Real cand;
			do {
				((Bridge *)trigger)->getBounds((Region2D *)&rawBounds);
				cand = (Real)rawBounds.lo.x;
				bridgeBounds.lo.x = *(bridgeBounds.lo.x < cand ? &bridgeBounds.lo.x : &cand);
				cand = (Real)rawBounds.hi.x;
				bridgeBounds.hi.x = *(bridgeBounds.hi.x > cand ? &bridgeBounds.hi.x : &cand);
				cand = (Real)rawBounds.lo.y;
				bridgeBounds.lo.y = *(bridgeBounds.lo.y < cand ? &bridgeBounds.lo.y : &cand);
				cand = (Real)rawBounds.hi.y;
				bridgeBounds.hi.y = *(bridgeBounds.hi.y > cand ? &bridgeBounds.hi.y : &cand);
				trigger = trigger->getNext();
			} while (trigger != 0);
		}
	} else {
		return;
	}

	Int maxX, maxY;
	m_xOrigin = fast_float2long_round((float)floor((double)((bridgeBounds.lo.x - g_bfmeScaleBK) * g_bfmeScaleBK)));
	m_yOrigin = fast_float2long_round((float)floor((double)((bridgeBounds.lo.y - g_bfmeScaleBK) * g_bfmeScaleBK)));
	m_width = 0;
	m_height = 0;
	maxX = fast_float2long_round((float)ceil((double)((bridgeBounds.hi.x + g_bfmeScaleBK) * g_bfmeScaleBK)));
	maxY = fast_float2long_round((float)ceil((double)((bridgeBounds.hi.y + g_bfmeScaleBK) * g_bfmeScaleBK)));

	// Pad with 1 extra.
	m_xOrigin--;
	m_yOrigin--;
	maxX++;
	maxY++;

	if (m_xOrigin < extent->lo.x) m_xOrigin = extent->lo.x;
	if (m_yOrigin < extent->lo.y) m_yOrigin = extent->lo.y;
	if (maxX > extent->hi.x) maxX = extent->hi.x;
	if (maxY > extent->hi.y) maxY = extent->hi.y;
	if (maxX <= m_xOrigin) return;
	if (maxY <= m_yOrigin) return;
	m_width = maxX - m_xOrigin;
	m_height = maxY - m_yOrigin;

	m_blockOfMapCells = new PathfindCell[m_width * m_height];
	m_layerCells = new PathfindCellP[m_width];
	for (Int i = 0; i < m_width; i++)
		m_layerCells[i] = &m_blockOfMapCells[i * m_height];
}
