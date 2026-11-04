// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F6F60 and 0x003F7020: the two 146-byte list-release walks that
// follow PathfindCell::reset and the out-of-line releaseInfo body (0x003F6F10,
// Rva003F7380State::finishReset) in AIPathfind order. Each walks an intrusive
// PathfindCellInfo list (+0x2C next, +0x30 back-link), unlinks the record,
// clears one list bit in the +0x24 flags (0x08 at 0x003F6F60, 0x10 at
// 0x003F7020), then runs the inlined releaseInfo test on the record's cell and
// returns the number of records walked. PathfindCellInfoPoolReset reaches
// 0x003F7020 through ILT 0x000135AC. The behaviour matches Zero Hour's
// PathfindCell::releaseOpenList / releaseClosedList, but no BFME caller or
// symbol proves those names, so the bodies keep address-derived names.
//
// Shape note: the +0x24 flags must be a bit-field view (bits 3 and 4 as
// one-bit fields, like Zero Hour's m_open / m_closed). A plain mask on an
// unsigned int leaves the walk count in EBX where retail uses EBP.

extern void *g_rva012F1094;

class MixFileInfoBuffer
{
public:
	void releaseInto(void *pool);
};

class PathfindCellInfo;

class PathfindCell
{
public:
	inline void releaseInfo();

	PathfindCellInfo *m_info;
	char m_pad04[8];
	unsigned int m_packed;
};

class PathfindCellInfo
{
public:
	void unlink()
	{
		if (m_back)
		{
			*m_back = m_next;
			if (m_next)
				m_next->m_back = m_back;
			m_back = 0;
			m_next = 0;
		}
	}

	char m_pad00[0x24];
	unsigned int m_lowFlags : 3;
	unsigned int m_open : 1;
	unsigned int m_closed : 1;
	unsigned int m_highFlags : 27;
	PathfindCell *m_cell;
	PathfindCellInfo *m_next;
	PathfindCellInfo **m_back;
};

// Inlined here; its out-of-line retail copy is 0x003F6F10.
// ?releaseInfo@PathfindCell@@QAEXXZ present-unmatched
inline void PathfindCell::releaseInfo()
{
	unsigned int packed = m_packed;
	if ((packed & 7) != 4 && (packed & 0x38) == 0 && (packed & 0x80000) == 0 &&
		m_info && m_info->m_back == 0 && !m_info->m_open && !m_info->m_closed)
	{
		reinterpret_cast<MixFileInfoBuffer *>(m_info)->releaseInto(&g_rva012F1094);
		m_info = 0;
	}
}

namespace Rva003F6F60 {
int method(void *p)
{
	if (p == 0) return 0;
	PathfindCellInfo *list = (PathfindCellInfo *)p;
	int count = 0;
	while (list)
	{
		++count;
		PathfindCellInfo *cur = list;
		list = cur->m_next;
		cur->unlink();
		cur->m_open = 0;
		PathfindCell *cell = cur->m_cell;
		if (cell)
			cell->releaseInfo();
	}
	return count;
}
}
