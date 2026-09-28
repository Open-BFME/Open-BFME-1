// cl: /DNDEBUG /MD
//
// Retail 0x003EAC80: Pathfinder::adjustToPossibleDestination.  Identity: the
// matched OpenContain::exitObjectInAHurry (0x002289F0) and exitObjectViaDoor
// (0x002284D0) reach this body through ILT 0x00011252 at the call site of Zero
// Hour's TheAI->pathfinder()->adjustToPossibleDestination(exitObj,
// ai->getLocomotorSet(), &endPosition), and the body is Zero Hour's spiral
// search (AIPathfind.cpp) on BFME's compact movement profile.  The body ends
// at 0x003EB0D4 (1108 bytes): the gen_asm row stopped seven bytes short, before
// the final `pop ebp; add esp,0x50; ret 0xc`.
//
// BFME differences from Zero Hour: TerrainLogic::getLayerForDestination takes
// the object; the crusher/surface pair is replaced by the PathfindMovementProfile
// the zone manager consumes, built from the object's template the way
// Pathfinder::validMovementPosition (0x003DB520) builds it; checkForPossible
// (0x003D6210, the Zero Hour body shape: getCell, impassable reject, effective
// zone of the goal cell, terrain zone when starting in an obstacle, compare,
// adjust) takes that profile; and the destination test is the six-argument
// wrapper at 0x003E6E90 around the eight-argument query at 0x003DF580, which
// retail calls out of line for the goal cell and expands inline in the spiral.
//
// Frame: retail's 0x50 bytes need the goal-cell block, the adjusted
// destination and the start cell in their own scopes, so the four spiral
// blocker slots can reuse them.  worldToCell carries its body here, marked
// noinline so the calls still bind to the matched body: with a
// declaration-only callee the object and destination swap ESI/EDI.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned short zoneStorageType;

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

extern "C" __declspec(dllimport) double __cdecl floor( double );

// BFME's REAL_TO_INT_FLOOR, as in inputs/reference/shims/pathfind/GameLogic/AIPathfind.h.
__forceinline Real fast_float_floor( Real f )
{
	return (Real)floor( (double)f );
}

__forceinline long fast_float2long_round( Real f )
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D( const Coord3D &o ) : x(o.x), y(o.y), z(o.z) {}
};
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { LAYER_GROUND = 0 };

// Layout of the profile PathfindZoneManager::getEffectiveZone reads
// (PathfindZoneTerrain.cpp).
struct PathfindMovementProfile
{
	int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	int layer;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vptr;
	const Overridable *m_nextOverride;
};

// Template fields as Pathfinder::validMovementPosition (0x003DB520) reads them.
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0x444 - 8];
	Int m_pathfindMaxLayer;
	unsigned char m_pad448[0x4cc - 0x448];
	unsigned char m_aircraftGoalFlag;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeIsComputerControlled() const;
	Int getLayer() const;
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *d = m_template;
		if (d == 0)
			return d;
		return (const ThingTemplate *)(d->m_nextOverride ? d->m_nextOverride->getFinalOverride() : d);
	}
	const Coord3D *getPosition() const { return &m_position; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorSet
{
public:
	Int getValidSurfaces() const { return m_validLocomotorSurfaces; }

private:
	unsigned char m_pad[0x10];
	Int m_validLocomotorSurfaces;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination( Object *object, const Coord3D *position );
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	enum CellType { CELL_OBSTACLE = 4 };
	zoneStorageType getZone() const { return m_zone; }
	CellType getType() const { return (CellType)(m_packed & 7); }

private:
	void *m_info;
	Int m_unused04;
	zoneStorageType m_zone;
	unsigned short m_unused0A;
	unsigned int m_packed;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(
		const PathfindMovementProfile &profile, zoneStorageType zone ) const;
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone ) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool adjustToPossibleDestination( Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest );
	Bool worldToCell( const Coord3D *worldPosition, ICoord2D *cellIndex );
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );
	PathfindCell *getClippedCell( PathfindLayerEnum layer, const Coord3D *pos )
	{
		ICoord2D cell;
		worldToCell( pos, &cell );
		return getCell( layer, cell.x, cell.y );
	}
	Bool checkForPossible( const PathfindMovementProfile &profile, Int fromZone, Bool center,
		Int cellX, Int cellY, PathfindLayerEnum layer, Coord3D *dest, Bool startingInObstacle );
	Bool bfmeInnerE6E90( Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer,
		Int radius, Bool centerInCell, void **blocker, Int flags );
	Bool bfmeWrapE6E90( Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer,
		Int radius, Bool centerInCell );
	Bool bfmeWrapE6E90Inline( Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer,
		Int radius, Bool centerInCell );

protected:
	void getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell );

private:
	unsigned char m_prefix[0x14];			// +0x000 opaque
	IRegion2D m_extent;						// +0x014
	unsigned char m_mid[0xc9c - 0x24];		// +0x024 opaque
	PathfindZoneManager m_zoneManager;		// +0xC9C
};

// Retail 0x003D7EC0; logic of pathfind_getcell.cpp.
__declspec(noinline) Bool Pathfinder::worldToCell( const Coord3D *worldPosition, ICoord2D *cellIndex )
{
	cellIndex->x = REAL_TO_INT_FLOOR(worldPosition->x/PATHFIND_CELL_SIZE);
	cellIndex->y = REAL_TO_INT_FLOOR(worldPosition->y/PATHFIND_CELL_SIZE);
	Bool overflow = false;
	if (cellIndex->x < m_extent.lo.x) {overflow = true; cellIndex->x = m_extent.lo.x;}
	if (cellIndex->y < m_extent.lo.y) {overflow = true; cellIndex->y = m_extent.lo.y;}
	if (cellIndex->x > m_extent.hi.x) {overflow = true; cellIndex->x = m_extent.hi.x;}
	if (cellIndex->y > m_extent.hi.y) {overflow = true; cellIndex->y = m_extent.hi.y;}
	return overflow;
}

// The logic of the out-of-line wrapper at 0x003E6E90 (Pathfinder_d_003e6e90.cpp),
// which retail expands inline inside the spiral.
// ?bfmeWrapE6E90Inline@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@H_N@Z absent-from-retail
inline Bool Pathfinder::bfmeWrapE6E90Inline( Object *obj, Int cellX, Int cellY,
	PathfindLayerEnum layer, Int radius, Bool centerInCell )
{
	void *blocker;
	if (!bfmeInnerE6E90( obj, cellX, cellY, layer, radius, centerInCell, &blocker, 0 ))
		return false;
	return blocker == 0;
}

Bool Pathfinder::adjustToPossibleDestination( Object *obj, const LocomotorSet &locomotorSet,
	Coord3D *dest )
{
	Int radius;
	Bool center;
	getRadiusAndCenter( obj, radius, center );
	Int i, j;
	Int zone1;
	Bool isObstacle;
	PathfindLayerEnum destinationLayer;
	PathfindMovementProfile profile;
	{
		ICoord2D goalCellNdx;
		{
			Coord3D adjustDest = *dest;
			if (!center) {
				adjustDest.x += PATHFIND_CELL_SIZE_F/2;
				adjustDest.y += PATHFIND_CELL_SIZE_F/2;
			}
			if (worldToCell( &adjustDest, &goalCellNdx )) {
				return false; // outside of bounds.
			}
		}

		// determine goal cell
		PathfindCell *goalCell;
		destinationLayer = TheTerrainLogic->getLayerForDestination( obj, dest );

		goalCell = getCell( destinationLayer, goalCellNdx.x, goalCellNdx.y );

		Coord3D from = *obj->getPosition();

		// determine start cell
		{
			ICoord2D startCellNdx;
			worldToCell( &from, &startCellNdx );
		}
		PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
		PathfindCell *parentCell = getClippedCell( layer, &from );
		if (parentCell == 0) {
			return false;
		}

		Int maxLayer = obj->getTemplate()->m_pathfindMaxLayer;
		unsigned char aircraftGoalFlag = obj->getTemplate()->m_aircraftGoalFlag;
		Bool computerControlled = obj->bfmeIsComputerControlled();
		profile.acceptableSurfaces = locomotorSet.getValidSurfaces();
		profile.crusher = aircraftGoalFlag == 0;
		profile.terrainOnly = computerControlled;
		profile.layer = maxLayer - 1;

		Int zone2;
		zone1 = m_zoneManager.getEffectiveZone( profile, parentCell->getZone() );
		isObstacle = false;
		if (parentCell->getType() == PathfindCell::CELL_OBSTACLE) {
			isObstacle = true;
		}
		if (isObstacle) {
			zone1 = m_zoneManager.bfmeEffectiveTerrainZone( profile, zone1 );
			zone1 = m_zoneManager.getEffectiveZone( profile, zone1 );
		}

		zone2 = m_zoneManager.getEffectiveZone( profile, goalCell->getZone() );

		if (zone1 == zone2) {
			if (bfmeWrapE6E90( obj, goalCellNdx.x, goalCellNdx.y, destinationLayer, radius, center )) {
				return true;
			}
		}
		i = goalCellNdx.x;
		j = goalCellNdx.y;
	}

	enum {MAX_CELLS_TO_TRY=400};
	Int limit = MAX_CELLS_TO_TRY;

	Int delta=1;
	Int count;
	while (limit>0) {
		for (count = delta; count>0; count--) {
			i++;
			limit--;
			if (checkForPossible( profile, zone1, center, i, j, destinationLayer, dest, isObstacle )) {
				if (bfmeWrapE6E90Inline( obj, i, j, destinationLayer, radius, center )) {
					return true;
				}
			}
		}
		for (count = delta; count>0; count--) {
			j++;
			limit--;
			if (checkForPossible( profile, zone1, center, i, j, destinationLayer, dest, isObstacle )) {
				if (bfmeWrapE6E90Inline( obj, i, j, destinationLayer, radius, center )) {
					return true;
				}
			}
		}
		delta++;
		for (count = delta; count>0; count--) {
			i--;
			limit--;
			if (checkForPossible( profile, zone1, center, i, j, destinationLayer, dest, isObstacle )) {
				if (bfmeWrapE6E90Inline( obj, i, j, destinationLayer, radius, center )) {
					return true;
				}
			}
		}
		for (count = delta; count>0; count--) {
			j--;
			limit--;
			if (checkForPossible( profile, zone1, center, i, j, destinationLayer, dest, isObstacle )) {
				if (bfmeWrapE6E90Inline( obj, i, j, destinationLayer, radius, center )) {
					return true;
				}
			}
		}
		delta++;
	}
	return false;
}
