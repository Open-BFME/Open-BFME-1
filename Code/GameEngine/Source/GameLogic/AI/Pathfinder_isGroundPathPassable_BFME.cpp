struct Coord3D;

struct ICoord2D
{
	int x;
	int y;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND
};

class Pathfinder;

struct GroundPathPassableInfo
{
	Pathfinder *pathfinder;
	int pathDiameter;
};

class Pathfinder
{
public:
	bool isGroundPathPassable(const Coord3D &startWorld,
		PathfindLayerEnum startLayer, const Coord3D &endWorld,
		int pathDiameter);

private:
	void worldToCell(const Coord3D *point, ICoord2D *cell);
	int iterateCellsAlongLine(const ICoord2D &startCell,
		const ICoord2D &endCell, PathfindLayerEnum layer,
		GroundPathPassableInfo *info);
};

bool Pathfinder::isGroundPathPassable(const Coord3D &startWorld,
	PathfindLayerEnum startLayer, const Coord3D &endWorld,
	int pathDiameter)
{
	GroundPathPassableInfo info;
	ICoord2D endCell;
	ICoord2D startCell;

	info.pathfinder = this;
	info.pathDiameter = pathDiameter;
	worldToCell(&startWorld, &startCell);
	worldToCell(&endWorld, &endCell);

	return iterateCellsAlongLine(startCell, endCell, startLayer, &info) == 0;
}
