// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x003D6210 (181 bytes, ret 0x20), Pathfinder::checkForPossible.
//
// IDENTITY: proven in
// targets/game/reverse/identity_evidence/003d6210-checkForPossible.md. The
// byte-matched Pathfinder::adjustToPossibleDestination (0x003EAC80,
// PathfinderAdjustToPossibleDestination.cpp) declares
//
//   Bool checkForPossible( const PathfindMovementProfile &profile, Int fromZone,
//       Bool center, Int cellX, Int cellY, PathfindLayerEnum layer,
//       Coord3D *dest, Bool startingInObstacle );
//
// and calls it four times through ILT 0x00018BE7 -> 0x003D6210. Nothing
// carries the older `checkForAdjust` label and it does not fit the body.
//
// The body is Zero Hour's Pathfinder::checkForPossible
// (AIPathfind.cpp:5515) with BFME's compact PathfindMovementProfile threaded
// through in place of the LocomotorSet's (acceptableSurfaces, isCrusher) pair:
// getCell, the impassable and layer-mismatch rejects, the bit-21 (occupied)
// test that the profile's terrainOnly flag vetoes, the goal cell's effective
// zone, the terrain zone when starting in an obstacle, the zone compare, then
// adjustCoordToCell and the success return.
//
// The Pathfinder and PathfindCell layouts restate the ones the matched
// PathfindCheckDestination.cpp and PathfindAdjustToPossibleDestination.cpp
// TUs already carry, so this TU declares its own copies rather than editing a
// shared header.
//
// No /alternatename is needed here. This TU spells Coord3D as a struct, so the
// helper call spells
//   ?adjustCoordToCell@Pathfinder@@IAEXHH_NAAUCoord3D@@W4PathfindLayerEnum@@@Z
// and binds straight to the matched body at 0x003D6040. Retail reaches that
// body through the ILT thunk 0x000411D2, a five-byte jmp. The class-tag
// (AAVCoord3D) /alternatename that PathfinderAdjustDestination003F6090.cpp
// carries cannot match a struct-spelled call.

// /EHsc is kept: retail registers no exception handler for this body because
// nothing here needs unwinding, and /EHsc emits none when that is true.

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

// The compact BFME movement profile: the pair of ZoneBlock flags the Zero Hour
// twin spells as separate arguments (getValidSurfaces, isCrusher) is one
// twelve-byte record whose zone-manager overloads take by reference. Offset
// +5 is the crusher/terrainOnly flag the body reads at +0x50.
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
	// Out of line: retail calls both through a thunk, so they must not be
	// inlined here. Both live in PathfindZoneTerrain.cpp.
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile,
		zoneStorageType zone) const;

	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;
};

// PathfindCell: the packed word at +0x0c carries the cell type in bits 0..2,
// the layer in bits 6..11 and the occupied bit at 21; the zone is the word at
// +0x8. The layout follows the matched PathfindCheckDestination.cpp body.
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
	Bool checkForPossible(const PathfindMovementProfile &profile, Int fromZone,
		Bool center, Int cellX, Int cellY, PathfindLayerEnum layer,
		Coord3D *dest, Bool startingInObstacle);

	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);

protected:
	// Protected on purpose: the matched retail helper is
	// ?adjustCoordToCell@Pathfinder@@IAEXHH_NAAUCoord3D@@W4PathfindLayerEnum@@@Z
	// at 0x003D6040 (functions.csv), and MSVC encodes access in the mangled
	// name, so the declaration has to sit in the protected section for the
	// call below to bind to it.  Retail calls the ILT thunk 0x000411D2, which
	// is a five-byte jmp to that very body, so binding straight to 0x003D6040
	// is the same target.
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &position, PathfindLayerEnum layer);

	unsigned char m_pad[0xc9c];
	PathfindZoneManager m_zoneManager;
};

Bool Pathfinder::checkForPossible(const PathfindMovementProfile &profile,
	Int fromZone, Bool center, Int cellX, Int cellY, PathfindLayerEnum layer,
	Coord3D *dest, Bool startingInObstacle)
{
	PathfindCell *cell;
	unsigned int flags;
	unsigned int type;
	Int zone;

	cell = getCell(layer, cellX, cellY);
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

	if ((unsigned char)(flags >> 21) & 1)
	{
		if (profile.terrainOnly)
			goto lateFailure;
	}

	// The cell's own zone is copied into a local first, as Zero Hour spells
	// the call `getEffectiveZone(..., goalCell->getZone())` against a local
	// assignment. It is load bearing: it gives the argument the rotation step
	// retail emits before the call.
	zoneStorageType cellZone = cell->m_zone;
	zone = m_zoneManager.getEffectiveZone(profile, cellZone);
	if (startingInObstacle)
		zone = m_zoneManager.bfmeEffectiveTerrainZone(profile,
			(zoneStorageType)zone);
	if (fromZone == zone)
	{
		adjustCoordToCell(cellX, cellY, center, *dest, layer);
		return true;
	}

lateFailure:
	return false;
}
