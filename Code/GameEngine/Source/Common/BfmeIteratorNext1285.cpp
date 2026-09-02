// cl: /O2 /DNDEBUG /MD

struct BfmeIterator1285
{
	void *m_data;
	void *m_extra;
};

extern BfmeIterator1285 g_emptyStringData;

class BfmeIteratorList1285
{
	int m_count;
	BfmeIterator1285 *m_array;

public:
	BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *cur);
};

BfmeIterator1285 *BfmeIteratorList1285::bfmeNext1285(BfmeIterator1285 *cur)
{
	BfmeIterator1285 *arr = m_array;
	if (arr == 0)
		return 0;

	BfmeIterator1285 *p = cur + 1;
	BfmeIterator1285 *end = arr + m_count;
	if (p >= end)
		return 0;

	do
	{
		void *data = p->m_data;
		if (data != 0 && data != &g_emptyStringData)
			return p;
		++p;
	}
	while (p < end);

	return 0;
}
