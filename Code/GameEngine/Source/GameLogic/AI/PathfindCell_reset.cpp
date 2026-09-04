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
	PathfindCellInfo *info = m_info;
	if (info != 0) {
		info->releaseToPool(g_pathfindCellInfoPool);
		m_info = 0;
	}

	unsigned int flags = m_pathFlags;
	flags &= 0xfe000040;
	flags |= 0x40;
	m_zoneAndGoals = 0;
	m_layerFlags = 0;
	m_cellTypeAndUnitFlags = 0;
	m_pathFlags = flags;
}
