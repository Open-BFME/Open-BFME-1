// cl: /DNDEBUG /MD /EHsc

extern "C" unsigned char g_pathfindCellInfoPool[];

class PathfindCellInfo
{
public:
	void releaseToPool(void *pool);
};

class PathfindCell
{
public:
	void reset();

private:
	PathfindCellInfo *m_info;
	int m_zoneAndGoals;
	unsigned short m_cellTypeAndUnitFlags;
	unsigned short m_layerFlags;
	unsigned int m_pathFlags;
};

void PathfindCell::reset()
{
	PathfindCellInfo *cellInfoRecord = m_info;
	if (cellInfoRecord != 0) {
		cellInfoRecord->releaseToPool(g_pathfindCellInfoPool);
		m_info = 0;
	}

	unsigned int resetPathFlags = m_pathFlags;
	resetPathFlags &= 0xfe000040;
	resetPathFlags |= 0x40;
	m_zoneAndGoals = 0;
	m_layerFlags = 0;
	m_cellTypeAndUnitFlags = 0;
	m_pathFlags = resetPathFlags;
}
