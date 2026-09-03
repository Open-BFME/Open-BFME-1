// ?releaseClosedList@PathfindCellInfo@@SAHPAV1@@Z
// partial score=0.76 date=2026-09-03
// BFME compact info-list release bodies, retail 0x003F6F60/0x003F7020.
// cl: /DNDEBUG /MD /EHsc

class PathfindCell;

class PathfindCellInfo
{
public:
	static int releaseOpenList(PathfindCellInfo *list);
	static int releaseClosedList(PathfindCellInfo *list);

	char m_pad00[0x24];
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

class MixFileInfoBuffer
{
public:
	void releaseInto(void *head);
};

extern int TheMixFileInfoPool;


int PathfindCellInfo::releaseOpenList(PathfindCellInfo *list)
	{
	if (list == 0) return 0;
	int count = 0;
	while (list)
	{
		PathfindCellInfo *current = list;
		PathfindCellInfo **back = current->m_back;
		PathfindCellInfo *next = current->m_next;
		list = next;
		++count;
		if (back)
		{
			*back = list;
			if (list)
				list->m_back = back;
			current->m_back = 0;
			current->m_next = 0;
		}

		unsigned int flags = current->m_flags;
		PathfindCell *cell = current->m_cell;
		current->m_flags = flags & ~8u;
		if (cell)
		{
			unsigned int packed = cell->m_packed;
			if ((packed & 7) != 4 && (packed & 0x38) == 0 &&
				(packed & 0x80000) == 0 && cell->m_info != 0 &&
				cell->m_info->m_back == 0 &&
				(cell->m_info->m_flags & 0x18) == 0)
			{
				reinterpret_cast<MixFileInfoBuffer *>(cell->m_info)->releaseInto(&TheMixFileInfoPool);
				cell->m_info = 0;
			}
		}
	}
	return count;
}

int PathfindCellInfo::releaseClosedList(PathfindCellInfo *list)
{
	register PathfindCell *cell;
	register PathfindCellInfo *cur = list;
	if (cur == 0) return 0;
	int count = 0;
	while (cur)
	{
		PathfindCellInfo *node = cur;
		PathfindCellInfo **back = node->m_back;
		PathfindCellInfo *next = node->m_next;
		cur = next;
		++count;
		if (back)
		{
			*back = cur;
			if (cur)
				cur->m_back = back;
			node->m_back = 0;
			node->m_next = 0;
		}

		unsigned int flags = node->m_flags;
		cell = node->m_cell;
		node->m_flags = flags & ~16u;
		if (cell)
		{
			unsigned int packed = cell->m_packed;
			if ((packed & 7) != 4 && (packed & 0x38) == 0 &&
				(packed & 0x80000) == 0 && cell->m_info != 0 &&
				cell->m_info->m_back == 0 &&
				(cell->m_info->m_flags & 0x18) == 0)
			{
				reinterpret_cast<MixFileInfoBuffer *>(cell->m_info)->releaseInto(&TheMixFileInfoPool);
				cell->m_info = 0;
			}
		}
	}
	return count;
}
