// ?startPathfind@PathfindCell@@QAE_NPAV1@@Z
// partial score=0.35 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

struct PathfindCellInfoView
{
	PathfindCellInfoView *m_prevFree;
	PathfindCellInfoView *m_nextFree;
	PathfindCellInfoView *m_pathParent;
	void *m_unknown0c;
	unsigned short m_costSoFar;
	unsigned short m_totalCost;
	char m_pad14[0x10];
	unsigned int m_flags;
	char m_pad28[4];
	PathfindCellInfoView *m_prevOpen;
	PathfindCellInfoView *m_nextOpen;
};

class PathfindCell
{
public:
	Bool startPathfind(PathfindCell *goalCell);

private:
	PathfindCellInfoView *m_info;
};

Bool PathfindCell::startPathfind(PathfindCell *)
{
	PathfindCellInfoView *next = m_info->m_nextOpen;
	if (next)
	{
		next->m_prevFree = m_info->m_prevOpen;
		PathfindCellInfoView *prev = m_info->m_prevOpen;
		if (prev)
			prev->m_nextOpen = m_info->m_nextOpen;
		m_info->m_nextOpen = 0;
		m_info->m_prevOpen = 0;
	}
	m_info->m_pathParent = 0;
	m_info->m_totalCost = 0;
	m_info->m_costSoFar = 0;
	m_info->m_flags &= ~8u;
	m_info->m_flags &= ~16u;
	return true;
}
