// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath
//
// Retail 0x003D84A0 (113 bytes): Pathfinder::rva003D84A0(Waypoint *).
// Owner: the receiver is Pathfinder -- it calls the matched
// Pathfinder::worldToCell (0x003D7EC0 via ILT 0x000171E8) on `this`, reads
// m_map@+0x10 and m_extent@+0x14..+0x20 exactly as the pathfind shim proves,
// and both retail callers (0x001F96E0+0x315, 0x0041BAC0+0x1C6) load ecx from
// TheAI+0xc. The method name is not proven, so it keeps the address token.
// The argument's position is at +0x0c (Zero Hour Waypoint::m_location); the
// Waypoint type is the one the matched zone-manager callee at 0x00403310
// already takes. Cell +0x04 holds the pointer the matched cell setter at
// 0x003F68F0 attaches; it is named by offset only.
//
// Helper visibility is required: with the authentic worldToCell body visible
// (noinline), VC7.1 knows the cell out-parameter is not retained, keeps
// cell.x/cell.y in callee-saved registers across the later calls and loads
// them straight into ebx/edi as retail does. With worldToCell opaque the same
// source reloads the pair (119 bytes) and a local-copy spelling rotates the
// callee-saved registers. The emitted worldToCell also matches 0x003D7EC0.

#include "coord.h"

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
extern "C" __declspec(dllimport) double __cdecl floor(double);

class Waypoint
{
public:
	const Coord3D *getLocation(void) const { return &m_location; }

private:
	void *m_vtbl;
	Int m_dword4;
	void *m_dword8;
	Coord3D m_location;
};

// Placeholder spellings the ledger holds for the cell setter at 0x003F68F0.
class Rva001A1DE0Owner;

class Gen_003F68F0
{
public:
	void bfmeAttach(Rva001A1DE0Owner *child);
};

class PathfindCell
{
public:
	void *getPtr4(void) const { return m_ptr4; }

private:
	void *m_info;
	void *m_ptr4;
	Int m_dword8;
	UnsignedInt m_packed;
};

class PathfindZoneManager
{
public:
	void bfmeSetWaypoint(Int cellX, Int cellY, Bool insert, Waypoint *waypoint);
};

class Pathfinder
{
public:
	__declspec(noinline) Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	void rva003D84A0(Waypoint *waypoint);

private:
	// Ground-map subset of the layer-aware getCell, as in PathfinderGetLayer.cpp.
	__forceinline PathfindCell *getGroundCell(Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
			return (PathfindCell *)((unsigned char *)m_map[x] +
				y * sizeof(PathfindCell));
		return 0;
	}

	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0xc9c - 0x24];
	PathfindZoneManager m_zoneManager;
};

Bool Pathfinder::worldToCell(const Coord3D *pos, ICoord2D *cell)
{
	cell->x = REAL_TO_INT_FLOOR(pos->x/10);
	cell->y = REAL_TO_INT_FLOOR(pos->y/10);
	Bool overflow = false;
	if (cell->x < m_extent.lo.x) {overflow = true; cell->x = m_extent.lo.x;}
	if (cell->y < m_extent.lo.y) {overflow = true; cell->y = m_extent.lo.y;}
	if (cell->x > m_extent.hi.x) {overflow = true; cell->x = m_extent.hi.x;}
	if (cell->y > m_extent.hi.y) {overflow = true; cell->y = m_extent.hi.y;}
	return overflow;
}

void Pathfinder::rva003D84A0(Waypoint *waypoint)
{
	ICoord2D cell;
	worldToCell(waypoint->getLocation(), &cell);
	PathfindCell *pathCell = getGroundCell(cell.x, cell.y);
	if (pathCell && pathCell->getPtr4() == 0)
	{
		((Gen_003F68F0 *)pathCell)->bfmeAttach((Rva001A1DE0Owner *)waypoint);
		m_zoneManager.bfmeSetWaypoint(cell.x, cell.y, true, waypoint);
	}
}
