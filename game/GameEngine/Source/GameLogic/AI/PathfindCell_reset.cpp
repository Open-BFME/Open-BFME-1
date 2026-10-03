// cl: /DNDEBUG /MD /EHsc

extern void *g_rva012F1094;

// Retail reaches PathfindCellInfo::releaseToPool through the five-byte ILT
// thunk at RVA 0x000203D8 (`?j_000203d8@@YAXXZ`, body 0x007F6E10), which is the
// only definition of that address in the ledger. Naming the thunk keeps the
// reference resolvable at link time and reproduces retail's call rel32.
extern void j_000203d8();

class PathfindCellInfo
{
public:
	void releaseToPool(void *pool);
};

static __forceinline void bfmeReleaseToPool(PathfindCellInfo *info, void *pool)
{
	union
	{
		void (*raw)();
		void (PathfindCellInfo::*member)(void *);
	} call;

	call.raw = j_000203d8;
	(info->*call.member)(pool);
}

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
		bfmeReleaseToPool(cellInfoRecord, &g_rva012F1094);
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
