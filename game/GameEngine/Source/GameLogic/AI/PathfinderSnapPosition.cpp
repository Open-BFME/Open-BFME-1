// readable body of ?snapPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *destinationPosition);
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
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
	ICoord2D cellIndex;
	Bool center;
	getRadiusAndCenter(object, cellIndex.x, center);
	Int centerInCell = *(volatile const Int *)&center;
	Coord3D adjustDest;
	adjustDest.x = destinationPosition->x;
	adjustDest.y = destinationPosition->y;
	adjustDest.z = destinationPosition->z;
	if (!(*(Bool *)&centerInCell)) {
		adjustDest.x += PATHFIND_CELL_SIZE_F / 2;
		adjustDest.y += PATHFIND_CELL_SIZE_F / 2;
	}
	worldToCell(&adjustDest, &cellIndex);
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(object, destinationPosition);
	adjustCoordToCell(cellIndex.x, cellIndex.y, *(Bool *)&centerInCell, *destinationPosition, layer);
}
