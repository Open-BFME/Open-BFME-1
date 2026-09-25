// readable body of ?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// ?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z
// partial score=0.82 date=2026-09-02
//
// Retail 0x003E6A30: Pathfinder::snapPosition, Zero Hour twin at
// AIPathfind.cpp:5106.  BFME asks TerrainLogic for the destination layer
// instead of hardcoding LAYER_GROUND.

typedef int Int;
typedef bool Bool;
typedef float Real;

#define PATHFIND_CELL_SIZE_F 10.0f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *destinationPosition);
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void snapPosition(Object *object, Coord3D *destinationPosition);
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);

protected:
	void getRadiusAndCenter(const Object *object, Int &radius, Bool &centerInCell);
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &position, PathfindLayerEnum layer);
};

// ?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z
void Pathfinder::snapPosition(Object *object, Coord3D *destinationPosition)
{
	Object *o = object;
	ICoord2D cell;
	Bool center;
	getRadiusAndCenter(o, cell.x, center);
	Int centerInCell = *(volatile const Int *)&center;
	Coord3D *p = destinationPosition;
	Coord3D adjustDest;
	adjustDest.x = p->x;
	adjustDest.y = p->y;
	adjustDest.z = p->z;
	if (!(*(Bool *)&centerInCell)) {
		adjustDest.x += PATHFIND_CELL_SIZE_F / 2;
		adjustDest.y += PATHFIND_CELL_SIZE_F / 2;
	}
	worldToCell(&adjustDest, &cell);
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(o, destinationPosition);
	adjustCoordToCell(cell.x, cell.y, *(Bool *)&centerInCell, *destinationPosition, layer);
}
