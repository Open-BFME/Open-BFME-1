// 0x007558B0 -- sort a 4-byte pointer vector then drop trailing objects whose
// first dword is zero.
//
//     construct a 4-byte comparator on the extra stack slot / call the
//     introsort driver at 0x00755820 / while back()->head == 0, operator
//     delete and pop_back.
//
// The driver is already landed. operator delete is the matched ??3@YAXPAX@Z.

struct Q3SortItem003CDC60
{
	int m_head;
};

struct Q3SortElem4
{
	Q3SortItem003CDC60 *m_item;
};

struct Q3SortCompare
{
	bool m_flag;
};

void Rva00755820(Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare cmp);

class Gen007558B0
{
public:
	void sortAndPrune(void);

private:
	Q3SortElem4 *m_start;
	Q3SortElem4 *m_finish;
};

// ?sortAndPrune@Gen007558B0@@QAEXXZ
void Gen007558B0::sortAndPrune(void)
{
	Q3SortElem4 *finish = m_finish;
	Q3SortElem4 *start = m_start;
	Q3SortCompare cmp;

	cmp.m_flag = false;
	Rva00755820(start, finish, cmp);

	while (m_start != m_finish)
	{
		Q3SortItem003CDC60 *item = (m_finish - 1)->m_item;

		if (item->m_head != 0)
			break;

		operator delete(item);
		--m_finish;
	}
}
