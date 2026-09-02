typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D;

struct ICoord2D
{
	int x;
	int y;
};

class PathfindCell
{
public:
	char m_bfmeHead[0x0c];
	unsigned int m_bfmeFlags;
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	Bool bfmeGroundCellThreshold(const Coord3D *pos, Bool requireClearType);
};

Bool Pathfinder::bfmeGroundCellThreshold(const Coord3D *pos, Bool requireClearType)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(LAYER_GROUND, cellIndex.x, cellIndex.y);
		if (cell != 0)
		{
			unsigned int flags = cell->m_bfmeFlags;
			char value = (char)((flags >> 6) & 0x3f);
			if (value > 0x10)
			{
				if (!requireClearType || (flags & 7) == 0)
					return true;
			}
		}
	}
	return false;
}
