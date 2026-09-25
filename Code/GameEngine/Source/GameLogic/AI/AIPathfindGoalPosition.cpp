// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?goalPosition@Pathfinder@@QAE_NPAVObject@@PAUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

// BFME stores these pathfinding fields at different offsets than the later
// Zero Hour Object layout used by the shared headers.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char Prefix[0x9C];
	int PathfindGoalX;
	int PathfindGoalY;
	unsigned char Middle[0x204 - 0xA4];
	void *AIUpdate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool goalPosition(Object *object, Coord3D *position);

protected:
	void getRadiusAndCenter(Object const *object, int &radius, bool &center);
	void adjustCoordToCell(int cellX, int cellY, bool centerInCell,
		Coord3D &position, PathfindLayerEnum layer);
};

bool Pathfinder::goalPosition(Object *object, Coord3D *outputPosition)
{
	if (!object->AIUpdate)
		return false;

	int objectRadius;
	bool centerInCell;
	getRadiusAndCenter(object, objectRadius, centerInCell);

	int goalCellX = object->PathfindGoalX;
	int goalCellY = object->PathfindGoalY;
	outputPosition->x = 0.0f;
	outputPosition->y = 0.0f;
	outputPosition->z = 0.0f;
	if (goalCellX < 0 || goalCellY < 0)
		return false;

	adjustCoordToCell(goalCellX, goalCellY, centerInCell, *outputPosition, LAYER_GROUND);
	return true;
}
