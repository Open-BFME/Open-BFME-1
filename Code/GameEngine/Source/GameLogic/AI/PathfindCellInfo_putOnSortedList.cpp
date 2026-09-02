// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F6B70: walk a back-pointer list until a record whose cost at +0x10
// outranks this one, unlink self, then splice in at that slot.

class PathfindCell;

class PathfindCellInfo
{
public:
	void putOnSortedList(PathfindCellInfo **head);

	PathfindCellInfo *m_infoViaCell;
	char m_pad04[0x0C];
	unsigned short m_totalCost;
	char m_pad12[0x16];
	PathfindCell *m_cell;
	PathfindCellInfo *m_next;
	PathfindCellInfo **m_back;
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
};

void PathfindCellInfo::putOnSortedList(PathfindCellInfo **head)
{
	PathfindCellInfo *cur = *head;
	PathfindCellInfo **slot = head;
	if (cur)
	{
		PathfindCell *cell = cur->m_cell;
		if (cell)
		{
			unsigned short cost = m_totalCost;
			do
			{
				cur = cell->m_info;
				if (cur->m_totalCost > cost)
					break;
				slot = &cur->m_next;
				cur = *slot;
				if (!cur)
					break;
				cell = cur->m_cell;
			} while (cell);
		}
	}

	if (m_back)
	{
		*m_back = m_next;
		if (m_next)
			m_next->m_back = m_back;
		m_back = 0;
		m_next = 0;
	}

	m_back = slot;
	PathfindCellInfo *first = *slot;
	m_next = first;
	if (first)
		first->m_back = &m_next;
	*slot = this;
}
