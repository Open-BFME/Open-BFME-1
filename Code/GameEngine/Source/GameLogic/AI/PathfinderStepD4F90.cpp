// cl: /DNDEBUG /MD
//
// Retail 0x003D4F90: the per-cell movement predicate used by the BFME
// Pathfinder walk.  The ILT at 0x0002B9E0 names this body from the
// Pathfinder examine callback.

typedef int Int;

struct BfmeMovementPositionInfo
{
	Int m_surfaces;
	unsigned char m_field04;
	unsigned char m_allowAircraftGoal;
	unsigned char m_pad06[2];
	Int m_maxLayer;
};

struct PathfindCellInfo
{
	unsigned char m_pad00[0x20];
	Int m_obstacleID;
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
	unsigned char m_field04;
	unsigned char m_pad05[3];
	Int m_field08;
	unsigned int m_word;
};

extern Int g_Va012B49FC[];

class Pathfinder
{
public:
	bool bfmeStepD4F90( void *state, PathfindCell *cell );

private:
	unsigned char m_pad00[0x844];
	Int m_ignoreObstacleID;
};

bool Pathfinder::bfmeStepD4F90( void *state, PathfindCell *cell )
{
	const PathfindCell *toCell = cell;
	register BfmeMovementPositionInfo *info = (BfmeMovementPositionInfo *)state;
	if (toCell == 0)
		return false;

	unsigned int word = toCell->m_word;
	if (((unsigned char)(word >> 21) & 1) != 0 &&
		info->m_allowAircraftGoal != 0)
		return false;

	Int type = word & 7;
	switch (type)
	{
	case 3:
		goto typeThree;

	case 4:
		break;

	default:
		goto common;
	}

	{
		Int obstacleID = toCell->m_info != 0 ?
			toCell->m_info->m_obstacleID : 0;
		if (obstacleID != m_ignoreObstacleID)
			goto common;
		goto passable;
	}

common:
	if ((g_Va012B49FC[type] & info->m_surfaces) == 0)
		return false;

	if (info->m_field04 != 0 && ((unsigned char)(word >> 20) & 1) != 0)
		return false;

	if (info->m_maxLayer < 0)
		goto passable;

	if ((Int)((word >> 22) & 3) > info->m_maxLayer)
		return false;

passable:
	return true;

typeThree:
	if ((word & 0xfc0) != 0x40)
		return false;

	goto common;
}
