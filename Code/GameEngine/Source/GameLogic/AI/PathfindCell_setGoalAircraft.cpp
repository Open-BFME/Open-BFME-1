// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F71D0: PathfindCell::setGoalAircraft. INVALID_ID is 0. The
// aircraft-goal flag is bit 19 of the packed dword at +0x0C. Release goes
// through the already-matched finishReset; allocate is the compact pool
// acquire at 0x012F1094.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	static void allocateCellInfos(void);

	char m_pad[0x1C];
	unsigned int m_goalAircraftID;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	void setGoalAircraft(unsigned int unitID, const ICoord2D &pos);

private:
	PathfindCellInfo *m_info;
	char m_pad[8];
	unsigned int m_packed;
};

void PathfindCell::setGoalAircraft(unsigned int unitID, const ICoord2D &pos)
{
	if (unitID == 0)
	{
		if (m_info)
		{
			m_info->m_goalAircraftID = unitID;
			m_packed &= ~0x80000u;
			((Rva003F7380State *)this)->finishReset();
		}
	}
	else
	{
		if (m_info == 0)
		{
			if (g_bfmePathfindFreeList == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, &pos);
		}
		m_info->m_goalAircraftID = unitID;
		m_packed |= 0x80000u;
	}
}
