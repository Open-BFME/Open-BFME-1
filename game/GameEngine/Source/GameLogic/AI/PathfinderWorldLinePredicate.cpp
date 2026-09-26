// Converts two world points to cells and reports whether the BFME cell walk
// completed without the callback reporting a hit.

typedef bool Bool;

struct Coord3D;

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
	int bfmeWalkWorldCells(const ICoord2D &startCell, const ICoord2D &endCell,
		int layer, const Coord3D **context);
	Bool bfmeWorldLineHasNoHit(const Coord3D *startPosition, const Coord3D *endPosition);
};

// ?bfmeWorldLineHasNoHit@Pathfinder@@QAE_NPBUCoord3D@@0@Z
Bool Pathfinder::bfmeWorldLineHasNoHit(const Coord3D *startPosition,
	const Coord3D *endPosition)
{
	ICoord2D startCell;
	ICoord2D endCell;
	worldToCell(startPosition, &startCell);
	worldToCell(endPosition, &endCell);
	return bfmeWalkWorldCells(startCell, endCell, 1, &startPosition) == 0;
}
