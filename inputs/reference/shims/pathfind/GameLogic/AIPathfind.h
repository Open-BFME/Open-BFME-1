#pragma once

// Retail calls the CRT floor() through the import table directly at the call
// site (`call dword ptr [__imp__floor]`, FF 15) rather than through a plain
// `e8`-to-ILT-thunk extern call that <math.h>'s ordinary declaration would
// produce here. A `dllimport` prototype forces MSVC to emit the same
// indirect-through-IAT call shape at every use, matching retail's codegen.
extern "C" __declspec(dllimport) double __cdecl floor(double);
// TU-scoped shim: retail-accurate PathfindCell/PathfindLayer/Pathfinder layout,
// proven byte-for-byte from retail bytes (not the ZH reference tree, which
// packs PathfindCell into 8B with a nibble@+7 instead of retail's 16B struct
// with a packed dword@+0xc). Only the fields a landed function actually reads
// are named; everything else is opaque padding, so this shim CANNOT regress
// a function that doesn't touch it. Shadow this path (private /I
// reference/shims/pathfind, placed before the ZH reference include dirs) only
// from TUs that need the retail layout - never from the shared AIPathfind.cpp,
// whose many already-matched functions rely on the ZH header instead.
//
// Proven facts, re-verified against retail bytes for this shim:
//   PathfindCell   sizeof 0x10. Packed dword@+0x0c: type:3@0, layer:6@6,
//                  connect:6@12 (ZH instead packs an 8B struct, nibble@+7).
//                  m_info (MemoryPoolObject-owned side table) stays @+0x00,
//                  matching ZH - proven by the already-matched clearParentCell/
//                  getGoalUnit/getPosUnit/setParentCell*, which only touch it.
//   PathfindLayer  sizeof 0x44 (ZH ~0x38). m_layerCells@+0x04, m_width@+0x08,
//                  m_height@+0x0c, m_xOrigin@+0x10, m_yOrigin@+0x14 - all
//                  UNSHIFTED vs ZH (proven: already-matched setZone@+0x2c,
//                  getStartCellIndex@+0x18, getEndCellIndex@+0x20 decode from
//                  the SAME retail offsets ZH declares). m_destroyed@+0x34,
//                  m_bridge@+0x38 (ZH bridge@+0x30) - the tail grew/reordered;
//                  proven from PathfindLayer::classifyCells's retail bytes.
//   Pathfinder     m_map@+0x10, m_extent (IRegion2D: lo.x/lo.y/hi.x/hi.y)
//                  @+0x14..+0x20 - proven from Pathfinder::worldToCell and
//                  Pathfinder::getCell(layer,x,y) retail bytes (identical
//                  arithmetic/offsets to the ZH inline body). m_layers[]@+0x85c
//                  with PathfindLayer stride 0x44 - proven by the `imul
//                  eax,eax,0x44` / `lea ecx,[eax+esi+0x85c]` in
//                  Pathfinder::getCell(layer,x,y)'s retail body (0x3D4E80).
//                  m_zoneManager@+0xc9c (ZH +0x54, 67 lea sites) is documented
//                  but not modeled here - no landed function in this TU needs it.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
struct Coord3D { Real x, y, z; };

// BFME redefines fast_float_floor to call the CRT floor() (fld;fmul;fstp
// qword;call [__imp__floor];fistp - see re_attempts.log worldToCell entry),
// NOT ZH BaseType.h's bit-trick (which never calls out). fast_float2long_round
// is unchanged (still the plain fld/fistp x87 round). TU-scoped here rather
// than in WWLib/basetype.h: every REAL_TO_INT_FLOOR call site in the tree is
// present-unmatched, so nothing byte-matched depends on the ZH bit-trick, but
// the fix belongs with the shim that proved it, not a blind global edit.
#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

extern Bool ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2,
                        IRegion2D *clipRegion);

__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

class Locomotor;

// Ordinal-only: mangling needs the enum's name, not its enumerators. Retail's
// range check (Pathfinder::getCell) accepts 2..15 inclusive - LAYER_LAST is
// therefore 15, one below the 16-slot m_layers[] array declared below.
enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

class PathfindCell
{
public:
	// Only the type nibble (bits 0-2 of the packed dword@+0x0c) is read by any
	// function in this shim; retail's PathfindLayer::getCell rejects type==5
	// (CELL_BRIDGE_IMPASSABLE) rather than ZH's CELL_IMPASSABLE(6) - the type
	// ordinals differ between the two trees, so this is a raw literal, not a
	// named enumerator.
	Int getRawType(void) const { return m_packed & 0x7; }
	Int getType(void) const { return m_packed & 0x7; }
	Int getLayer(void) const { return (m_packed >> 6) & 0x3f; }

private:
	void *m_info;          // +0x00 (matches ZH; unread here)
	Int   m_unused1;        // +0x04
	Int   m_unused2;        // +0x08
	unsigned int m_packed;  // +0x0c  type:3@0 layer:6@6 connect:6@12
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);

private:
	void          *m_blockOfMapCells; // +0x00 (unread here)
	PathfindCell **m_layerCells;      // +0x04
	Int            m_width;           // +0x08
	Int            m_height;          // +0x0c
	Int            m_xOrigin;         // +0x10
	Int            m_yOrigin;         // +0x14
	unsigned char  m_tail[0x44 - 0x18]; // opaque: m_startCell..m_bridge/m_destroyed etc.
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool validMovementTerrain(Int layer, const Locomotor *locomotor, const Coord3D *pos);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	void clip(Coord3D *from, Coord3D *to);

private:
	unsigned char  m_prefix[0x10]; // opaque: base vtable slots + m_blockOfMapCells
	PathfindCell **m_map;          // +0x10
	IRegion2D      m_extent;       // +0x14 (lo.x/lo.y/hi.x/hi.y)
	unsigned char  m_mid[0x85c - 0x24]; // opaque: m_logicalExtent..m_zoneManager etc.
	PathfindLayer  m_layers[16];   // +0x85c, stride 0x44 (LAYER_LAST+1 == 16)
};
