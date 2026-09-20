// ?setArea@Pathfinder@@QAEXPAVPolygonTrigger@@_N@Z
// partial score=0.07 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F7AB0, 424 bytes.
//
// Reached through Code/GameEngine/Source/GameLogic/ScriptEngine/Rva002F73B0AreaForwarder.cpp's
// bfmeSetArea() helper (its raw function pointer j_00030b98 thunks to this
// body -- reverse/functions.csv: ?j_00030b98@@YAXXZ,...,target=FUN_007f7ab0).
// That TU calls the pointer through a two-argument (void *, Bool) member
// shape, matching the ret 8 / 2-arg cleanup here.
//
// The receiver's own layout (PathfindCell **m_map at +0x10, IRegion2D
// m_extent at +0x14, PathfindZoneManager m_zoneManager at +0xc9c) is byte-
// identical to the already-landed Pathfinder::classifyFence
// (Code/GameEngine/Source/GameLogic/AI/PathfinderClassifyFence.cpp), so this
// body keeps that class/field naming even though the caller-side TU's own
// placeholder name for the pointer type is "AreaManager".
//
// Shape: getBounds() fills a float Region2D, each edge is truncated to a
// pathfind cell coordinate (signed divide-by-10 via the 0x66666667 magic
// constant), then every cell whose center point falls inside the area
// (pointInTrigger) and inside m_extent has its 0x200000 obstacle-in-area bit
// set/cleared to 'blocked'. Any touched cell's rectangle is tracked and
// passed to markZonesDirty, exactly as classifyFence does for its fence
// footprint (including its same cellBounds.hiY-vs-hiX comparison).

typedef float Real;
typedef int Int;
typedef bool Bool;

#define PATHFIND_CELL_SIZE_F 10.0f

struct ICoord3D
{
	Int x, y, z;
};

struct IRegion2D
{
	Int loX, loY, hiX, hiY;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
// Address-derived: both proven call targets (0x0000FEE8, 0x0004AB6F) are
// reached through this same pointer, so both are declared on it here.
class PolygonTrigger
{
public:
	void getBounds(IRegion2D *bounds) const;			// retail 0x0000FEE8
	Bool pointInTrigger(const ICoord3D &point) const;	// retail 0x0004AB6F
};

class PathfindCell
{
public:
	unsigned int getFlags() const { return *(unsigned int *)((char *)this + 0xc); }
	void setFlags(unsigned int v) { *(unsigned int *)((char *)this + 0xc) = v; }

private:
	char m_pad[16];
};

class PathfindZoneManager
{
public:
	void markZonesDirty(const IRegion2D *bounds, Bool b);	// retail 0x004030D0

private:
	Bool m_bfmeDirty;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void setArea(PolygonTrigger *area, Bool blocked);

private:
	char m_pad00[0x10];
	PathfindCell **m_map;			// +0x10
	IRegion2D m_extent;				// +0x14
	char m_pad24[0xc9c - 0x24];
	PathfindZoneManager m_zoneManager;	// +0xc9c
};

// ?setArea@Pathfinder@@QAEXPAVPolygonTrigger@@_N@Z
void Pathfinder::setArea(PolygonTrigger *area, Bool blocked)
{
	IRegion2D bounds;
	area->getBounds(&bounds);

	Int loX = bounds.loX / 10;
	Int loY = bounds.loY / 10;
	Int hiX = bounds.hiX / 10;
	Int hiY = bounds.hiY / 10;

	IRegion2D cellBounds;
	cellBounds.loX = 0x7fffffff;
	cellBounds.loY = 0x7fffffff;
	cellBounds.hiX = -1;
	cellBounds.hiY = -1;

	for (Int cx = loX; cx <= hiX; ++cx)
	{
		for (Int cy = loY; cy <= hiY; ++cy)
		{
			ICoord3D cellPos;
			cellPos.x = cx * (Int)PATHFIND_CELL_SIZE_F + 5;
			cellPos.y = cy * (Int)PATHFIND_CELL_SIZE_F + 5;

			if (!area->pointInTrigger(cellPos))
				continue;

			if (cx < m_extent.loX || cx > m_extent.hiX ||
				cy < m_extent.loY || cy > m_extent.hiY)
				continue;

			unsigned int flags = m_map[cx][cy].getFlags();
			flags ^= (((unsigned int)blocked << 0x15) ^ flags) & 0x200000;
			m_map[cx][cy].setFlags(flags);

			if (cx < cellBounds.loX) cellBounds.loX = cx;
			if (cy < cellBounds.loY) cellBounds.loY = cy;
			cellBounds.hiX = (cx > cellBounds.hiX) ? cx : cellBounds.hiX;
			cellBounds.hiY = (cy > cellBounds.hiX) ? cy : cellBounds.hiY;
		}
	}

	if (cellBounds.hiX != -1)
	{
		m_zoneManager.markZonesDirty(&cellBounds, false);
	}
}
