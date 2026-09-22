// ?checkForAdjust@Rva003D6210@@QAE_NABUPathfindMovementProfile@@H_NHHHPAUCoord3D@@1@Z
// partial score=0.65 date=2026-09-22
// Scratch-only full-body probe for retail 0x003D6210 (181 bytes).
// Owner and method name are address-derived pending root caller review.
// The parameter order is the independently decoded BFME body ABI:
// profile, expectedZone, center, cellX, cellY, layer, pos, terrainZone.
//
// FROM 0.23 TO 0.65 this session by matching CONTROL-FLOW SHAPE, not by
// touching identity or the callee ABI (those were already right):
//  - The three early rejects (cell==0, layer mismatch, type==4, type==5)
//    must each be a PLAIN `return false;`, not `goto` a single shared
//    label. Retail duplicates a tiny 4-instruction epilogue
//    (`pop edi; xor al,al; pop ebp; ret 0x20`) right after the checks and
//    reaches it with SHORT jumps from all three sites; routing all three
//    through one goto/label made MSVC place the shared epilogue far away
//    and use long (6-byte) conditional jumps instead of short (2-byte)
//    ones at every one of those sites -- this alone took the body from
//    182B/139diff to 178B/88diff.
//  - The LATER two rejects (bit21+terrainOnly, expectedZone mismatch) are
//    the OPPOSITE: they must stay a shared `goto lateFailure;` to a SINGLE
//    trailing `return false;` -- flattening those to plain `return false;`
//    each (matching the early-reject fix) duplicates that tail and drifts
//    every register choice downstream. Keeping early rejects flat and late
//    rejects shared took it from 88diff to 64diff (score 0.23 -> 0.65).
//  - `if (cell->m_bit21 && profile.terrainOnly) goto lateFailure;` must be
//    written as NESTED ifs (`if (m_bit21) { if (terrainOnly) goto ...; }`)
//    -- retail's compiled shape skips the terrainOnly read entirely when
//    m_bit21 is clear (a short jump straight past it), which `&&`
//    short-circuit evaluation does NOT reproduce as the same branch shape
//    even though it is logically identical.
//
// REMAINING 64-byte residue (not closed this session): a single-bit test
// of PathfindCell's bit 21. Retail is `shr ecx,0x15; test cl,1` (5 bytes);
// every source spelling tried here -- the union bitfield `cell->m_bit21`,
// `(flags>>21)&1`, and `flags & (1u<<21)` -- compiles to the same 6-byte
// `test ecx,0x200000` instead, and MSVC 7.1 never picks the shift+test-byte
// form for a lone single-bit test no matter how it is spelled (three
// spellings, identical output). That one instruction's extra byte then
// shifts every following branch target and downstream register choice
// (getEffectiveZone/bfmeEffectiveTerrainZone results end up in ecx here,
// eax in retail) without changing any logic -- all remaining diff bytes
// are downstream of that single instruction-selection difference.
// shape_family_levers.py --families test,bool,sib,register found no
// applicable automatic lever for it (no adjacent atom-initialized locals,
// no simple negated-call or reversed-bit-test pattern it recognizes).
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef bool Bool;
typedef unsigned short zoneStorageType;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
};

class PathfindCell
{
public:
	unsigned char m_pad00[8];
	zoneStorageType m_zone;

	private:
	unsigned short m_pad0a;

	public:
	union
	{
		unsigned int m_flags;
		struct
		{
			unsigned int m_type : 3;
			unsigned int m_unused0 : 18;
			unsigned int m_bit21 : 1;
			unsigned int m_unused1 : 10;
		};
	};
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);
	void adjustCoordToCell(Int cellX, Int cellY, Bool center,
		Coord3D &pos, PathfindLayerEnum layer);

protected:
	unsigned char m_pad[0xc9c];
	PathfindZoneManager m_zoneManager;
};

class Rva003D6210 : public Pathfinder
{
public:
	Bool checkForAdjust(const PathfindMovementProfile &profile,
		Int expectedZone, Bool center, Int cellX, Int cellY, Int layer,
		Coord3D *pos, Bool terrainZone);
};

Bool Rva003D6210::checkForAdjust(
	const PathfindMovementProfile &profile, Int expectedZone, Bool center,
	Int cellX, Int cellY, Int layer, Coord3D *pos, Bool terrainZone)
{
	PathfindCell *cell;
	unsigned int flags;
	unsigned int type;
	zoneStorageType zone;

	cell = getCell((PathfindLayerEnum)layer, cellX, cellY);
	if (cell == 0)
		return false;

	flags = cell->m_flags;
	if (((flags >> 6) & 0x3f) != (unsigned int)layer)
 		return false;
	type = flags & 7;
	if (type == 4)
		return false;
	if (type == 5)
		return false;

	if (cell->m_bit21)
	{
		if (profile.terrainOnly)
			goto lateFailure;
	}

	zone = m_zoneManager.getEffectiveZone(profile,
		cell->m_zone);
	if (terrainZone)
		zone = m_zoneManager.bfmeEffectiveTerrainZone(profile, zone);
	if (expectedZone != (Int)zone)
		goto lateFailure;

	adjustCoordToCell(cellX, cellY, center, *pos,
		(PathfindLayerEnum)layer);
	return true;

lateFailure:
	return false;
}
