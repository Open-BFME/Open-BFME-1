// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F70E0: PathfindCell::setGoalUnit. Goal id at info+0x14, pos id
// at +0x18. Packed flags live in bits 3-5 of the dword at cell+0x0C.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

class PathfindCell;
class PathfindCellInfo;

class Rva003F7380State
{
public:
	void finishReset();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	static void allocateCellInfos(void);

	char m_pad[0x14];
	unsigned int m_goalUnitID;
	unsigned int m_posUnitID;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeListHead, PathfindCell *pathfindCell,
	const ICoord2D *cellPosition);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	void setGoalUnit(unsigned int goalUnitID, const ICoord2D &cellPosition);

private:
	PathfindCellInfo *m_info;
	char m_pad[8];
	unsigned int m_packed;
};

void PathfindCell::setGoalUnit(unsigned int goalUnitID, const ICoord2D &cellPosition)
{
	if (goalUnitID == 0)
	{
		if (m_info)
		{
			m_info->m_goalUnitID = goalUnitID;
			if (m_info->m_posUnitID == 0)
			{
				m_packed &= ~0x38u;
				((Rva003F7380State *)this)->finishReset();
			}
			else
			{
				m_packed = (m_packed & ~0x28u) | 0x10u;
			}
		}
	}
	else
	{
		if (m_info == 0)
		{
			if (g_bfmePathfindFreeList == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, &cellPosition);
		}
		m_info->m_goalUnitID = goalUnitID;
		if (goalUnitID == m_info->m_posUnitID)
			m_packed = (m_packed & ~0x20u) | 0x18u;
		else if (m_info->m_posUnitID == 0)
			m_packed = (m_packed & ~0x30u) | 0x08u;
		else
			m_packed = (m_packed & ~0x18u) | 0x20u;
	}
}
