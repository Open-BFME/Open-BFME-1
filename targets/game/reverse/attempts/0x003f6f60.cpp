// ?method@Rva003F6F60@@YAHPAX@Z
// partial score=0.898 date=2026-09-27
// Retail 0x003F6F60: unlink PathfindCellInfo records, clear flag bit 3, and
// release eligible cell metadata. The best C++ probe emits 141 bytes, with
// 117 non-relocation bytes different from the 146-byte retail body.
// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class PathfindCell;

class PathfindCellInfo
{
public:
	static int releaseClosedList(PathfindCellInfo *list);
	void releaseToPool(void *pool);

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


extern PathfindCellInfo *g_bfmePathfindFreeList;

static __forceinline void unlinkRva003F6F60Node(
	PathfindCellInfo *current, PathfindCellInfo **back, PathfindCellInfo *next)
{
	if (back)
	{
		*back = next;
		if (next)
			next->m_back = back;
		current->m_back = 0;
		current->m_next = 0;
	}
}

namespace Rva003F6F60
{
int method(void *list)
{
	if (list == 0) return 0;
	int count = 0;
	do
	{
		PathfindCellInfo *current = (PathfindCellInfo *)list;
		PathfindCellInfo **back = current->m_back;
		_ReadWriteBarrier();
		PathfindCellInfo *next = current->m_next;
		list = next;
		++count;
		unlinkRva003F6F60Node(current, back, (PathfindCellInfo *)list);

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
				cell->m_info->releaseToPool(&g_bfmePathfindFreeList);
				cell->m_info = 0;
			}
		}
	} while (list);
	return count;
}
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
				cell->m_info->releaseToPool(&g_bfmePathfindFreeList);
				cell->m_info = 0;
			}
		}
	}
	return count;
}
