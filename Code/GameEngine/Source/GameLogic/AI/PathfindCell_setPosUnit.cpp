// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F7250: PathfindCell::setPosUnit. Pos id at info+0x18, goal id
// at +0x14. Same packed flag nibble as setGoalUnit.

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

	char m_pad[0x14];
	unsigned int m_goalUnitID;
	unsigned int m_posUnitID;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	void setPosUnit(unsigned int unitID, const ICoord2D &pos);

private:
	PathfindCellInfo *m_info;
	char m_pad[8];
	unsigned int m_packed;
};

void PathfindCell::setPosUnit(unsigned int unitID, const ICoord2D &pos)
{
	if (unitID == 0)
	{
		if (m_info)
		{
			m_info->m_posUnitID = unitID;
			if (m_info->m_goalUnitID == 0)
			{
				m_packed &= ~0x38u;
				((Rva003F7380State *)this)->finishReset();
			}
			else
			{
				m_packed = (m_packed & ~0x30u) | 0x08u;
			}
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
		if (m_info->m_goalUnitID != 0 && m_info->m_goalUnitID == m_info->m_posUnitID)
			return;
		m_info->m_posUnitID = unitID;
		if (unitID == m_info->m_goalUnitID)
			m_packed = (m_packed & ~0x20u) | 0x18u;
		else if (m_info->m_goalUnitID == 0)
			m_packed = (m_packed & ~0x28u) | 0x10u;
		else
			m_packed = (m_packed & ~0x18u) | 0x20u;
	}
}
