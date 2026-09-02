// ?bfmeFirst1285@BfmeIteratorList1285@@QAEPAUBfmeIterator1285@@XZ
// partial score=0.87 date=2026-09-02
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
	BfmeIterator1285 *bfmeFirst1285();
};

BfmeIterator1285 *BfmeIteratorList1285::bfmeFirst1285()
{
	BfmeIterator1285 *arr = m_array;
	if (arr == 0)
		return 0;

	int n = m_count;
	int i = 0;
	if (n > 0)
	{
		BfmeIterator1285 *walk = arr;
		do
		{
			void *data = *(void **)walk;
			if (data != 0 && data != &g_emptyStringData)
				return arr + i;
			++i;
			++walk;
		}
		while (i < n);
	}
	return 0;
}
