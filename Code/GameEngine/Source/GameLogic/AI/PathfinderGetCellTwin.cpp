// A second non-folded emission of Pathfinder's world-position getCell wrapper.

typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Coord3D;
class PathfindCell;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);
	PathfindCell *bfmeGetCellByIndicesTwin(PathfindLayerEnum layer, int cellX, int cellY);
	PathfindCell *bfmeGetCellTwin(PathfindLayerEnum layer, const Coord3D *worldPosition);
};

// ?bfmeGetCellTwin@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@PBUCoord3D@@@Z
PathfindCell *Pathfinder::bfmeGetCellTwin(PathfindLayerEnum layer, const Coord3D *worldPosition)
{
	ICoord2D cell;
	Bool overflow = worldToCell(worldPosition, &cell);
	if (overflow)
		return 0;
	return bfmeGetCellByIndicesTwin(layer, cell.x, cell.y);
}
