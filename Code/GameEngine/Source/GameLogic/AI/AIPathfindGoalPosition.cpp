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

bool Pathfinder::goalPosition(Object *object, Coord3D *position)
{
	if (!object->AIUpdate)
		return false;

	int radius;
	bool center;
	getRadiusAndCenter(object, radius, center);

	int cellX = object->PathfindGoalX;
	int cellY = object->PathfindGoalY;
	position->x = 0.0f;
	position->y = 0.0f;
	position->z = 0.0f;
	if (cellX < 0 || cellY < 0)
		return false;

	adjustCoordToCell(cellX, cellY, center, *position, LAYER_GROUND);
	return true;
}
