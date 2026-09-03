// cl: /DNDEBUG /MD /EHsc
// readable body of ?startPathfind@PathfindCell@@QAE_NPAV1@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// Retail 0x003F6940: PathfindCell::startPathfind. BFME unlinks the info record
// from the free list (back-pointer at +0x30, next at +0x2C), then clears the
// parent/cost/open/closed fields. The goalCell argument is unused (no
// costToGoal); the function still returns true.

typedef bool Bool;

class PathfindCell;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
struct PathfindCellInfo
{
	int m_first;
	int m_posY;
	PathfindCellInfo *m_pathParent;
	PathfindCellInfo *m_prevOpen;
	unsigned short m_totalCost;
	unsigned short m_costSoFar;
	char m_mid[0x10];
	unsigned int m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_prev;
	PathfindCellInfo *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Bool startPathfind(PathfindCell *goalCell);

private:
	PathfindCellInfo *m_info;
};

Bool PathfindCell::startPathfind(PathfindCell *)
{
	PathfindCellInfo *owner = m_info;
	PathfindCellInfo *next = owner->m_next;
	if (next != 0)
	{
		next->m_first = (int)owner->m_prev;
		PathfindCellInfo *previous = owner->m_prev;
		if (previous != 0)
			previous->m_next = owner->m_next;
		owner->m_next = 0;
		owner->m_prev = 0;
	}
	m_info->m_pathParent = 0;
	m_info->m_costSoFar = 0;
	m_info->m_totalCost = 0;
	m_info->m_flags &= ~8u;
	m_info->m_flags &= ~16u;
	return true;
}
