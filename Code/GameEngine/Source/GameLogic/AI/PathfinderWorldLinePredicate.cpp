// Converts two world points to cells and reports whether the BFME cell walk
// completed without the callback reporting a hit.

typedef bool Bool;

struct Coord3D;

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
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	int bfmeWalkWorldCells(const ICoord2D &start, const ICoord2D &end,
		int layer, const Coord3D **context);
	Bool bfmeWorldLineHasNoHit(const Coord3D *start, const Coord3D *end);
};

// ?bfmeWorldLineHasNoHit@Pathfinder@@QAE_NPBUCoord3D@@0@Z
Bool Pathfinder::bfmeWorldLineHasNoHit(const Coord3D *start, const Coord3D *end)
{
	ICoord2D startCell;
	ICoord2D endCell;
	worldToCell(start, &startCell);
	worldToCell(end, &endCell);
	return bfmeWalkWorldCells(startCell, endCell, 1, &start) == 0;
}
