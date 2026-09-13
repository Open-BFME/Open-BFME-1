// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

// Pathfinder::buildHierachicalPath, retail 0x003E7A30.
// BFME records the parent chain in a 12-byte vector before it builds the Path.

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva003DDF00Element
{
	unsigned int m_value[3];
};

class Path;

struct PathfindCellInfo
{
	int m_pos[2];
	PathfindCellInfo *m_pathParent;
	PathfindCellInfo *m_prevOpen;
	unsigned short m_totalCost;
	unsigned short m_costSoFar;
	char m_mid[0x14];
	class PathfindCell *m_cell;
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;

	unsigned short getXIndex(void) const
	{
		return (unsigned short)m_info->m_pos[0];
	}

	unsigned short getYIndex(void) const
	{
		return (unsigned short)m_info->m_pos[1];
	}

	PathfindCell *getParentCell(void) const
	{
		return m_info ? m_info->m_pathParent ? m_info->m_pathParent->m_cell : 0 : 0;
	}
};

class Path
{
public:
	Path();

	int m_data[9];
};

class Pathfinder
{
protected:
	Path *buildHierachicalPath(const Coord3D *fromPos, PathfindCell *goalCell);

public:
	void prependCells(Path *path, const Coord3D *fromPos,
		PathfindCell *goalCell, Bool center);

private:
	char m_beforePathCellVector[0x2470c];
	std::vector<Rva003DDF00Element> m_pathCells;
};

Path *Pathfinder::buildHierachicalPath(const Coord3D *fromPos,
	PathfindCell *goalCell)
{
	Path *path;
	PathfindCellInfo *info;
	PathfindCell *currentCell = goalCell;
	PathfindCell *nextCell;
	Rva003DDF00Element element;
	for (;;)
	{
		if (currentCell->getParentCell() == 0)
			break;
		info = currentCell->m_info;

		if (info->m_prevOpen != 0)
		{
			element.m_value[0] = (unsigned int)info->m_prevOpen->m_pos[1];
			element.m_value[1] = currentCell->getParentCell()->getXIndex();
			element.m_value[2] = currentCell->getParentCell()->getYIndex();
			m_pathCells.push_back(element);
		}
		nextCell = currentCell->getParentCell();
		currentCell = nextCell;
	}

	path = new Path;
	prependCells(path, fromPos, goalCell, true);
	return path;
}
