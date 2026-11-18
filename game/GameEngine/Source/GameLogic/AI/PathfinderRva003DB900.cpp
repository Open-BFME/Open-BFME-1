// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x003DB900 (201 B, ret 8): Pathfinder::rva003DB900, the name its
// matched callers (PathfinderFindGroundPath.cpp, PathfinderInternalFindPath.cpp,
// PathfinderStepD4F90.cpp) declare and reach through ILT 0x0003A828. A leaf:
// walks the 12-byte point records at this+0x2470C/+0x24710 from the back,
// summing octile steps (10 straight / 14 diagonal) from the start cell, the
// running total doubled and 1400 added per point, then adds the plain octile
// step from the last point to the goal cell. Copying each point into a local
// ICoord2D is what keeps retail's separate x load before the subtract.

#include <stdlib.h>

#include "../../../Include/Common/ScalarTypes.h"



#include "../../../../Libraries/Include/Lib/ICoord2D.h"

struct PathfindCellInfo
{
	ICoord2D m_pos;
};

class PathfindCell
{
public:
	UnsignedShort getXIndex() const { return (UnsignedShort)m_info->m_pos.x; }
	UnsignedShort getYIndex() const { return (UnsignedShort)m_info->m_pos.y; }

private:
	PathfindCellInfo *m_info;
};

struct Rva003DB900Point
{
	Int m_unknown00;
	ICoord2D m_pos;
};

class Pathfinder
{
public:
	UnsignedInt rva003DB900(PathfindCell *cell, PathfindCell *goalCell);

private:
	char m_unmodelled[0x2470c];
	Rva003DB900Point *m_pointsBegin;
	Rva003DB900Point *m_pointsEnd;
};

UnsignedInt Pathfinder::rva003DB900(PathfindCell *cell, PathfindCell *goalCell)
{
	ICoord2D cur;
	cur.x = cell->getXIndex();
	cur.y = cell->getYIndex();
	UnsignedInt cost = 0;
	for (Rva003DB900Point *p = m_pointsEnd; p != m_pointsBegin; --p)
	{
		const Rva003DB900Point &point = *(p - 1);
		ICoord2D pos = point.m_pos;
		Int dx = abs(cur.x - pos.x);
		Int dy = abs(cur.y - pos.y);
		if (dx > dy)
			cost = 2 * (cost + 5 * dx + 2 * dy);
		else
			cost = 2 * (cost + 7 * dx + 5 * (dy - dx));
		cur = point.m_pos;
		cost += 1400;
	}
	Int dx = abs(cur.x - goalCell->getXIndex());
	Int dy = abs(cur.y - goalCell->getYIndex());
	if (dx > dy)
		return cost + 10 * dx + 4 * dy;
	return cost + 14 * dx + 10 * (dy - dx);
}
