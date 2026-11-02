// A second non-folded emission of Pathfinder's world-position getCell wrapper.

typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Coord3D;
class PathfindCell;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);
	PathfindCell *bfmeGetCellByIndicesTwin(PathfindLayerEnum layer, int cellX, int cellY);
	PathfindCell *bfmeGetCellTwin(PathfindLayerEnum layer, const Coord3D *worldPosition);
};

// The cell lookup is reached through ILT 0x00042249 (body 0x003D4F00), which the
// ledger defines as ?j_00042249@@YAXXZ; the call names it through a member pointer.
extern void j_00042249(void);

// ?bfmeGetCellTwin@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@PBUCoord3D@@@Z
PathfindCell *Pathfinder::bfmeGetCellTwin(PathfindLayerEnum layer, const Coord3D *worldPosition)
{
	ICoord2D cellIndex;
	Bool overflow = worldToCell(worldPosition, &cellIndex);
	if (overflow)
		return 0;
	union { void (*raw)(void); PathfindCell *(Pathfinder::*member)(PathfindLayerEnum, int, int); } call;
	call.raw = j_00042249;
	return (this->*call.member)(layer, cellIndex.x, cellIndex.y);
}
