// ?method@Rva008F80A0@@QAE_NHHH@Z
// partial score=0.2 date=2026-09-24
// cl: /O2

// ?method@Rva008F80A0@@QAE_NHHH@Z
//
// Called (twice) by the 0x008F82A0 helper for a row's x-range and its
// neighbour rows, and itself calls the matched
// ?getCellRange@PartitionManager@@QAEXPAPAVPartitionCell@@0HHH@Z
// (PartitionManager_getCellRange.cpp) to get the [first,last) cell run, then
// bump-allocates one 16-byte Element per cell from m_04..m_08 and head-links
// it into that PartitionCell's list -- the same intrusive list the sweep at
// 0x008F7EC0 (Rva008F7EC0Sweep.cpp) unlinks from.

class Element
{
public:
	void *m_cell;
	void *m_04;
	Element **m_pprev;
	Element *m_next;
};

class PartitionCell
{
public:
	Element *m_firstElem;
	unsigned char m_pad04[0x64];
};

class PartitionManager
{
public:
	void getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y);
};

class Rva008F80A0
{
public:
	bool method(int x1, int x2, int y);

	PartitionManager *m_00;
	Element *m_04;
	Element *m_08;
};

bool Rva008F80A0::method(int x1, int x2, int y)
{
	PartitionCell *first, *last;
	m_00->getCellRange(&first, &last, x1, x2, y);

	for (PartitionCell *cell = first; cell != last; cell = (PartitionCell *)((char *)cell + 0x68))
	{
		if (m_04 >= m_08)
			return false;

		Element *e = m_04;
		m_04 = e + 1;
		e->m_cell = cell;
		Element *head = cell->m_firstElem;
		e->m_next = head;
		if (head)
			head->m_pprev = &e->m_next;
		e->m_pprev = (Element **)cell;
		cell->m_firstElem = e;
	}
	return true;
}
