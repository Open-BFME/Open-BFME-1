// Small BFME cell-state predicates that share the world-to-cell/getCell path.

typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	char m_bfmeHead[0x0c];
	union
	{
		unsigned int m_bfmeFlags;
		struct
		{
			unsigned int m_bfmeType : 3;
			unsigned int m_bfmeGap0 : 15;
			unsigned int m_bfmeFlag18 : 1;
			unsigned int m_bfmeGap1 : 1;
			unsigned int m_bfmeFlag20 : 1;
			unsigned int m_bfmeGap2 : 11;
		};
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);

	int bfmeCellTypeTwo(const Coord3D *pos, PathfindLayerEnum layer);
	int bfmeCellTypeFourWithFlag(const Coord3D *pos, PathfindLayerEnum layer);
	int bfmeCellTypeTwoWithoutFlag(const Coord3D *pos, PathfindLayerEnum layer);
	int bfmeCellTypeFiveOrOutside(const Coord3D *pos, PathfindLayerEnum layer);
	Bool bfmeCellAvoidsThreeTypes(const Coord3D *pos, PathfindLayerEnum layer);
	int bfmeCellAvoidsThreeTypesInt(const Coord3D *pos, PathfindLayerEnum layer);
};

int Pathfinder::bfmeCellTypeTwo(const Coord3D *pos, PathfindLayerEnum layer)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(layer, cellIndex.x, cellIndex.y);
		if (cell != 0)
		{
			unsigned int flags = *(volatile unsigned int *)&cell->m_bfmeFlags;
			return (unsigned char)(flags & 7) == 2;
		}
	}
	return false;
}

int Pathfinder::bfmeCellTypeFourWithFlag(const Coord3D *pos, PathfindLayerEnum layer)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(layer, cellIndex.x, cellIndex.y);
		if (cell != 0)
		{
			unsigned int flags = cell->m_bfmeFlags;
			if (cell->m_bfmeType == 4)
			{
				flags >>= 20;
				if (((unsigned char)flags & 1) != 0)
					return true;
			}
		}
	}
	return false;
}

int Pathfinder::bfmeCellTypeTwoWithoutFlag(const Coord3D *pos, PathfindLayerEnum layer)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(layer, cellIndex.x, cellIndex.y);
		if (cell != 0)
		{
			unsigned int flags = cell->m_bfmeFlags;
			if (cell->m_bfmeType == 2)
			{
				flags >>= 18;
				if (((unsigned char)flags & 1) == 0)
					return true;
			}
		}
	}
	return false;
}

int Pathfinder::bfmeCellTypeFiveOrOutside(const Coord3D *pos, PathfindLayerEnum layer)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(layer, cellIndex.x, cellIndex.y);
		if (cell != 0)
			return (cell->m_bfmeFlags & 7) == 5;
	}
	return true;
}

Bool Pathfinder::bfmeCellAvoidsThreeTypes(const Coord3D *pos, PathfindLayerEnum layer)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(layer, cellIndex.x, cellIndex.y);
		if (cell == 0)
			return true;
		unsigned int type = cell->m_bfmeFlags & 7;
		if (type == 5)
			return false;
		if (type == 1)
			return false;
		if (type == 2)
			return false;
		return true;
	}
	return true;
}

int Pathfinder::bfmeCellAvoidsThreeTypesInt(const Coord3D *pos, PathfindLayerEnum layer)
{
	ICoord2D cellIndex;
	if (!worldToCell(pos, &cellIndex))
	{
		PathfindCell *cell = getCell(layer, cellIndex.x, cellIndex.y);
		if (cell == 0)
			return (Bool)1;
		unsigned int type = cell->m_bfmeFlags & 7;
		if (type == 5)
			return 0;
		if (type == 1)
			return 0;
		if (type == 2)
			return 0;
		return 1;
	}
	return 1;
}
