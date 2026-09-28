// ?d_003e6300@@YAXXZ
// partial score=0.26 date=2026-09-28
// cl: /DNDEBUG /MD
// ?d_003e6300@@YAXXZ -- banked rewrite, NOT a match (opaque symbol below:
// ?findReachableCellNear003E6300@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z).
// Retail 0x003E6300, 1462 bytes, RET 0xC at +0x5B3. Pathfinder receiver
// (m_zoneManager at +0xC9C, getRadiusAndCenter/worldToCell/getCell/
// checkDestination on ECX=this); the algorithm is Zero Hour
// adjustToPossibleDestination with BFME changes read from the disassembly:
// getLayerForDestination(obj, dest); the ZH isCrusher/locomotorSet pair is the
// 12-byte PathfindMovementProfile built exactly as the matched
// validMovementPosition (0x003DB520) builds it; getEffectiveTerrainZone takes
// the profile; and each candidate cell must also be closer to the unit than
// the original destination (squared distance from a copy of `from`).
// Rewritten from scratch: the old bank was a raw ZH port (997 bytes).
// Measured: 1421 of 1462 bytes, 994 differing non-relocation bytes.
// Remaining wall is register allocation: retail keeps this in EBX and dest in
// EBP for the whole body and spills destinationLayer to [esp+0x14]; this body
// puts this in EBP, destinationLayer in EBX and reloads dest from its argument
// slot inside the loop, so every loop block shifts. Frame is 0x5C vs 0x48.
// Callee 0x003D6210 (via ILT 0x00018BE7) is ZH checkForPossible in its body
// (getCell, layer and impassable checks, getEffectiveZone on the profile,
// adjustCoordToCell), but symbols.csv pins that ILT as checkForAdjust with an
// Object*/LocomotorSet* signature; landing needs that resolved first.
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned short zoneStorageType;

#define PATHFIND_CELL_SIZE_F 10.0f

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR, CELL_WATER, CELL_CLIFF, CELL_RUBBLE, CELL_OBSTACLE };
	CellType getType(void) const { return (CellType)m_type; }
	zoneStorageType getZone(void) const { return m_zone; }

private:
	void *m_info;
	Int m_unmodelled04;
	zoneStorageType m_zone;
	unsigned short m_unmodelled0A;
	unsigned int m_type : 3;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_opaque008[0x444 - 8];
	Int m_pathfindMaxLayer;
	unsigned char m_opaque448[0x4cc - 0x448];
	unsigned char m_aircraftGoalFlag;
};

class Object
{
public:
	Bool bfmeIsComputerControlled(void) const;
	Int getLayer(void) const;
	const ThingTemplate *getTemplate(void) const
	{
		if (m_template == 0)
			return 0;
		if (m_template->m_nextOverride)
			return (const ThingTemplate *)m_template->m_nextOverride->getFinalOverride();
		return m_template;
	}
	const Coord3D *getPosition(void) const { return &m_position; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_opaque008[0x38 - 8];
	Coord3D m_position;
};

class LocomotorSet
{
public:
	UnsignedInt getValidSurfaces(void) const { return m_validLocomotorSurfaces; }


	unsigned char m_opaque000[0x10];
	UnsignedInt m_validLocomotorSurfaces;
};

struct PathfindMovementProfile
{
	int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	int layer;

	void set(UnsignedInt surfaces, char aircraftGoalFlag, Bool computerControlled, Int maxLayer)
	{
		acceptableSurfaces = surfaces;
		crusher = aircraftGoalFlag == 0;
		terrainOnly = computerControlled;
		layer = maxLayer - 1;
	}
};

class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile, zoneStorageType zone) const;
	zoneStorageType bfmeEffectiveTerrainZone(const PathfindMovementProfile &profile, zoneStorageType zone) const;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	PathfindCell *getClippedCell(PathfindLayerEnum layer, const Coord3D *pos)
	{
		ICoord2D cell;
		worldToCell(pos, &cell);
		return getCell(layer, cell.x, cell.y);
	}
	Bool checkDestination(const Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer, Int iRadius, Bool center);
	Bool checkForPossible(const PathfindMovementProfile &profile, Int fromZone, Bool center,
		Int cellX, Int cellY, PathfindLayerEnum layer, Coord3D *dest, Bool startingInObstacle);
	Bool findReachableCellNear003E6300(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);

protected:
	void getRadiusAndCenter(const Object *obj, Int &iRadius, Bool &center);

private:
	unsigned char m_opaque000[0xc9c];
	PathfindZoneManager m_zoneManager;
};

Bool Pathfinder::findReachableCellNear003E6300(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest)
{
	Int radius;
	Bool center;
	getRadiusAndCenter(obj, radius, center);
	ICoord2D goalCellNdx;
	Coord3D adjustDest = *dest;
	if (!center) {
		adjustDest.x += PATHFIND_CELL_SIZE_F/2;
		adjustDest.y += PATHFIND_CELL_SIZE_F/2;
	}
	if (worldToCell(&adjustDest, &goalCellNdx)) {
		return false;
	}

	PathfindCell *goalCell;
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(obj, dest);
	goalCell = getCell(destinationLayer, goalCellNdx.x, goalCellNdx.y);

	Coord3D from = *obj->getPosition();
	Coord3D delta;
	delta.x = from.x - dest->x;
	delta.y = from.y - dest->y;
	delta.z = from.z - dest->z;
	Real startDistSqr = delta.x*delta.x + delta.y*delta.y + delta.z*delta.z;

	ICoord2D startCellNdx;
	worldToCell(&from, &startCellNdx);
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	PathfindCell *parentCell = getClippedCell(layer, &from);
	if (parentCell == 0) {
		return false;
	}

	PathfindMovementProfile profile;
	int n = obj->getTemplate()->m_pathfindMaxLayer;
	char f = obj->getTemplate()->m_aircraftGoalFlag;
	profile.set(locomotorSet.m_validLocomotorSurfaces, f, obj->bfmeIsComputerControlled(), n);

	Int zone1, zone2;
	zone1 = m_zoneManager.getEffectiveZone(profile, parentCell->getZone());
	Bool isObstacle = false;
	if (parentCell->getType() == PathfindCell::CELL_OBSTACLE) {
		isObstacle = true;
	}
	if (isObstacle) {
		zone1 = m_zoneManager.bfmeEffectiveTerrainZone(profile, zone1);
		zone1 = m_zoneManager.getEffectiveZone(profile, zone1);
	}

	zone2 = m_zoneManager.getEffectiveZone(profile, goalCell->getZone());

	if (zone1 == zone2) {
		if (checkDestination(obj, goalCellNdx.x, goalCellNdx.y, destinationLayer, radius, center)) {
			return true;
		}
	}

	enum {MAX_CELLS_TO_TRY=400};
	Int limit = MAX_CELLS_TO_TRY;
	Int i, j;
	i = goalCellNdx.x;
	j = goalCellNdx.y;

	Coord3D d;
	Int delta2 = 1;
	Int count;
	while (limit > 0) {
		for (count = delta2; count > 0; count--) {
			i++;
			limit--;
			if (checkForPossible(profile, zone1, center, i, j, destinationLayer, dest, isObstacle)) {
				d = from;
				d.x -= dest->x;
				d.y -= dest->y;
				d.z -= dest->z;
				if (d.x*d.x + d.y*d.y + d.z*d.z < startDistSqr) {
					if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
						return true;
					}
				}
			}
		}
		for (count = delta2; count > 0; count--) {
			j++;
			limit--;
			if (checkForPossible(profile, zone1, center, i, j, destinationLayer, dest, isObstacle)) {
				d = from;
				d.x -= dest->x;
				d.y -= dest->y;
				d.z -= dest->z;
				if (d.x*d.x + d.y*d.y + d.z*d.z < startDistSqr) {
					if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
						return true;
					}
				}
			}
		}
		delta2++;
		for (count = delta2; count > 0; count--) {
			i--;
			limit--;
			if (checkForPossible(profile, zone1, center, i, j, destinationLayer, dest, isObstacle)) {
				d = from;
				d.x -= dest->x;
				d.y -= dest->y;
				d.z -= dest->z;
				if (d.x*d.x + d.y*d.y + d.z*d.z < startDistSqr) {
					if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
						return true;
					}
				}
			}
		}
		for (count = delta2; count > 0; count--) {
			j--;
			limit--;
			if (checkForPossible(profile, zone1, center, i, j, destinationLayer, dest, isObstacle)) {
				d = from;
				d.x -= dest->x;
				d.y -= dest->y;
				d.z -= dest->z;
				if (d.x*d.x + d.y*d.y + d.z*d.z < startDistSqr) {
					if (checkDestination(obj, i, j, destinationLayer, radius, center)) {
						return true;
					}
				}
			}
		}
		delta2++;
	}
	return false;
}
