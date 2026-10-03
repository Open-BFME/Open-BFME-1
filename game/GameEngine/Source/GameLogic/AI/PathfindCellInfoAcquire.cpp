// BFME's compact 0x34-byte pathfind-cell info pool operations.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

class PathfindCell;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	static void allocateCellInfos(void);

	ICoord2D m_pos;                         // +0x00
	PathfindCellInfo *m_nextOpen;           // +0x08
	PathfindCellInfo *m_prevOpen;           // +0x0c
	unsigned short m_totalCost;             // +0x10
	unsigned short m_costSoFar;             // +0x12
	unsigned int m_pathParent;              // +0x14
	unsigned int m_goalUnitID;              // +0x18
	unsigned int m_posUnitID;               // +0x1c
	unsigned int m_goalAircraftID;          // +0x20
	unsigned int m_flags;                   // +0x24
	PathfindCell *m_cell;                   // +0x28
	PathfindCellInfo *m_freeNext;           // +0x2c
	PathfindCellInfo **m_freePrevLink;      // +0x30
};

// Retail RVA 0x003F6B2A/0x003F6B40 load/store this four-byte free-list head.
// VA 0x012F1094 is zero-filled; BFME's intrusive pool has no proven EA name.
void *g_rva012F1094 = 0;
int g_rva012F1098 = 0;                          // retail 0x012F1098

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeListHead, PathfindCell *pathfindCell, const ICoord2D *cellPosition)
{
	PathfindCellInfo *cellInfoRecord = *freeListHead;
	if (cellInfoRecord->m_freePrevLink != 0)
	{
		*cellInfoRecord->m_freePrevLink = cellInfoRecord->m_freeNext;
		if (cellInfoRecord->m_freeNext != 0)
			cellInfoRecord->m_freeNext->m_freePrevLink = cellInfoRecord->m_freePrevLink;
		cellInfoRecord->m_freePrevLink = 0;
		cellInfoRecord->m_freeNext = 0;
	}

	cellInfoRecord->m_cell = pathfindCell;
	cellInfoRecord->m_pos = *cellPosition;
	cellInfoRecord->m_nextOpen = 0;
	cellInfoRecord->m_prevOpen = 0;
	cellInfoRecord->m_totalCost = 0;
	cellInfoRecord->m_costSoFar = 0;
	cellInfoRecord->m_pathParent = 0;
	cellInfoRecord->m_goalUnitID = 0;
	cellInfoRecord->m_posUnitID = 0;
	cellInfoRecord->m_goalAircraftID = 0;
	cellInfoRecord->m_flags &= 0xffffffe0;
	++g_rva012F1098;
	return cellInfoRecord;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	void bfmeEnsureInfo(const ICoord2D *cellPosition);
	PathfindCellInfo *m_info;
};

void PathfindCell::bfmeEnsureInfo(const ICoord2D *cellPosition)
{
	if (m_info == 0)
	{
		if (g_rva012F1094 == 0)
			PathfindCellInfo::allocateCellInfos();
		m_info = bfmeAcquirePathfindCellInfo(reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), this, cellPosition);
	}
	else
	{
		m_info->m_prevOpen = 0;
	}
}
