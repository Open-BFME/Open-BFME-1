// ?costSoFar@PathfindCell@@QAEIPAV1@@Z
// partial score=0.92 date=2026-09-03
// ?costSoFar@PathfindCell@@QAEIPAV1@@Z
// BFME compact pathfind-cell info layout; recovered from retail 0x003F6D20.
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct ICoord2D
{
	int x;
	int y;
};

class PathfindCell;

struct PathfindCellInfo
{
	ICoord2D m_pos;
	PathfindCellInfo *m_pathParent;
	char m_pad0c[4];
	UnsignedShort m_totalCost;
	UnsignedShort m_costSoFar;
	char m_pad14[0x14];
	PathfindCell *m_cell;
};

class PathfindCell
{
public:
	UnsignedInt costSoFar(PathfindCell *parent);
	UnsignedShort getXIndex(void) const { return m_info->m_pos.x; }
	UnsignedShort getYIndex(void) const { return m_info->m_pos.y; }
	UnsignedInt getCostSoFar(void) const { return m_info->m_costSoFar; }
	PathfindCell *getParentCell(void) const
	{
		return m_info ? m_info->m_pathParent ? m_info->m_pathParent->m_cell : 0 : 0;
	}
	bool getPinched(void) const { return ((m_bits >> 18) & 1) != 0; }

private:
	PathfindCellInfo *m_info;
	char m_pad04[8];
	UnsignedInt m_bits;
};

UnsignedInt PathfindCell::costSoFar(PathfindCell *parent)
{
	if (parent == 0)
		return 0;

	ICoord2D prevDir;
	int cost;
	prevDir.x = parent->getXIndex() - m_info->m_pos.x;
	prevDir.y = parent->getYIndex() - m_info->m_pos.y;
	if (prevDir.x == 0 || prevDir.y == 0)
		cost = parent->getCostSoFar() + 10;
	else
		cost = parent->getCostSoFar() + 14;

	if (getPinched())
		cost += 14;

	int numTurns = 0;
	PathfindCellInfo *parentInfo = parent->m_info;
	if (parentInfo)
		parentInfo = parentInfo->m_pathParent;
	PathfindCell *prevCell;
	if (parentInfo)
		prevCell = parentInfo->m_cell;
	else
		prevCell = 0;
	if (prevCell)
	{
		ICoord2D dir;
		dir.x = prevCell->getXIndex() - parent->getXIndex();
		dir.y = prevCell->getYIndex() - parent->getYIndex();
		if (dir.x != prevDir.x || dir.y != prevDir.y)
		{
			int dot = dir.x * prevDir.x + dir.y * prevDir.y;
			if (dot > 0)
				numTurns = 4;
			else
			{
				numTurns = 8;
				if (dot < 0)
					numTurns = 16;
			}
		}
	}

	return cost + numTurns;
}
