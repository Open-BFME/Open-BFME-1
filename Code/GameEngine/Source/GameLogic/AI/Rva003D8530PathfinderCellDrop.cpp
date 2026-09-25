// cl: /DNDEBUG /MD /EHsc /Ireference/shims/pathfind
// ?bfmeDrop@Rva003D8530Owner@@QAEXPAX@Z
// Retail 0x003D8530, 112 bytes. The body converts the position at entry+0x0c
// to a cell with Pathfinder::worldToCell (0x003D7EC0), reads the ground cell
// inside m_extent, and when that cell's +0x04 link is entry it clears the link
// (0x003F68F0) and passes x, y, false and entry to the zone manager at +0xc9c
// (0x00403310). this is a Pathfinder: it is the receiver of worldToCell and
// every field offset is the one the pathfind shim proves. The method keeps the
// address-derived name the MemoryPool::~MemoryPool call (via ILT 0x00016DB0)
// already uses.
//
// worldToCell is defined in this TU, exactly as its matched body in
// pathfind_getcell.cpp, so that VC7.1 can see the conversion does not keep
// &cell. With that knowledge it holds cell.x and cell.y in EBX and EDI across
// both calls, as retail does, instead of copying them to locals (see
// docs/shape_levers.md, "AI pathfinding: authentic lookup visibility").
#include "GameLogic/AIPathfind.h"

class Rva001A1DE0Owner;
class Waypoint;

// The 16-byte PathfindCell under the ledger name of its 0x003F68F0 method.
class Gen_003F68F0
{
public:
	void bfmeAttach(Rva001A1DE0Owner *child);

	void *m_unused;
	Rva001A1DE0Owner *m_child;
	Int m_unused8;
	unsigned int m_unusedC;
};

class PathfindZoneManager
{
public:
	void bfmeSetWaypoint(Int cellX, Int cellY, Bool insert, Waypoint *waypoint);
};

Bool Pathfinder::worldToCell(const Coord3D *pos, ICoord2D *cell)
{
	cell->x = REAL_TO_INT_FLOOR(pos->x/PATHFIND_CELL_SIZE);
	cell->y = REAL_TO_INT_FLOOR(pos->y/PATHFIND_CELL_SIZE);
	Bool overflow = false;
	if (cell->x < m_extent.lo.x) {overflow = true; cell->x = m_extent.lo.x;}
	if (cell->y < m_extent.lo.y) {overflow = true; cell->y = m_extent.lo.y;}
	if (cell->x > m_extent.hi.x) {overflow = true; cell->x = m_extent.hi.x;}
	if (cell->y > m_extent.hi.y) {overflow = true; cell->y = m_extent.hi.y;}
	return overflow;
}

// Pathfinder fields this body reads, at the offsets the pathfind shim proves.
class Rva003D8530Owner
{
public:
	void bfmeDrop(void *entry);

private:
	// Ground-map subset of Pathfinder::getCell(layer, x, y), as in
	// PathfinderGetLayer.cpp; not a separate retail function.
	Gen_003F68F0 *getGroundCell(Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
			return &m_map[x][y];
		return 0;
	}

	unsigned char m_prefix[0x10];
	Gen_003F68F0 **m_map;                  // +0x10
	IRegion2D m_extent;                    // +0x14
	unsigned char m_mid[0xc9c - 0x24];
	PathfindZoneManager m_zoneManager;     // +0xc9c
};

void Rva003D8530Owner::bfmeDrop(void *entry)
{
	ICoord2D cell;
	reinterpret_cast<Pathfinder *>(this)->worldToCell(
		(const Coord3D *)((const char *)entry + 0x0c), &cell);

	Gen_003F68F0 *pathCell = getGroundCell(cell.x, cell.y);
	if (pathCell && pathCell->m_child == entry)
	{
		pathCell->bfmeAttach(0);
		m_zoneManager.bfmeSetWaypoint(cell.x, cell.y, false, (Waypoint *)entry);
	}
}
