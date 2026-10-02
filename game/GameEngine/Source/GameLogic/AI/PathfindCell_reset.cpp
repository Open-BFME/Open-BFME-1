// cl: /DNDEBUG /MD /EHsc

extern void *g_rva012F1094;

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
		cellInfoRecord->releaseToPool(&g_rva012F1094);
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
