// ?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x003E6A30: Pathfinder::snapPosition, Zero Hour twin at
// AIPathfind.cpp:5106.  BFME asks TerrainLogic for the destination layer
// instead of hardcoding LAYER_GROUND.

typedef int Int;
typedef bool Bool;
typedef float Real;

#define PATHFIND_CELL_SIZE_F 10.0f

struct Coord3D
{
	Real x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void snapPosition(Object *obj, Coord3D *pos);

protected:
	void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &pos, PathfindLayerEnum layer);
};

// ?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z
void Pathfinder::snapPosition(Object *obj, Coord3D *pos)
{
	Object *o = obj;
	ICoord2D cell;
	Bool center;
	getRadiusAndCenter(o, cell.x, center);
	Coord3D *p = pos;
	Coord3D adjustDest;
	adjustDest.x = p->x;
	adjustDest.y = p->y;
	adjustDest.z = p->z;
	if (!center) {
		adjustDest.x += PATHFIND_CELL_SIZE_F / 2;
		adjustDest.y += PATHFIND_CELL_SIZE_F / 2;
	}
	worldToCell(&adjustDest, &cell);
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(o, p);
	adjustCoordToCell(cell.x, cell.y, center, *p, layer);
}
