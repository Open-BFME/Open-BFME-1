// ?releaseOpenList@PathfindCellInfo@@SAHPAV1@@Z
// partial score=0.75 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F6F60: static releaseOpenList. Walks the compact info list,
// unlinks each record, clears the open bit, and releases the owning cell
// through the same guards as finishReset.

class PathfindCell;
class MixFileInfoBuffer
{
public:
	void releaseInto(void *head);
};

extern int TheMixFileInfoPool;

class PathfindCellInfo
{
public:
	static int releaseOpenList(PathfindCellInfo *list);

	char m_pad[0x24];
	unsigned int m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_next;
	PathfindCellInfo **m_back;
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
	char m_pad04[8];
	unsigned int m_packed;
};

int PathfindCellInfo::releaseOpenList(PathfindCellInfo *list)
{
	if (list == 0)
		return 0;

	PathfindCell *cell;
	int count = 0;
	do
	{
		PathfindCellInfo *cur = list;
		PathfindCellInfo **back = cur->m_back;
		PathfindCellInfo **slot = &list->m_next;
		list = *slot;
		count++;
		if (back)
		{
			PathfindCellInfo *saved = list;
			*back = saved;
			PathfindCellInfo *next = *slot;
			if (next)
				next->m_back = cur->m_back;
			cur->m_back = 0;
			*slot = 0;
		}
		cur->m_flags &= ~8u;
		cell = cur->m_cell;
		if (cell)
		{
			unsigned int flags = cell->m_packed;
			if ((flags & 7) != 4 && (flags & 0x38) == 0 &&
				(flags & 0x80000) == 0 && cell->m_info != 0 &&
				cell->m_info->m_back == 0 && (cell->m_info->m_flags & 0x18) == 0)
			{
				reinterpret_cast<MixFileInfoBuffer *>(cell->m_info)->releaseInto(&TheMixFileInfoPool);
				cell->m_info = 0;
			}
		}
	} while (list);
	return count;
}
