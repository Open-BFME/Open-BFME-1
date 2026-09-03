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
	BfmeIterator1285 *array = m_array;
	if (array == 0)
		return 0;

	int count = m_count;
	const BfmeIterator1285 *walk;
	int index = 0;
	if (count > 0)
	{
		walk = array;
		for (; index < count; ++index, ++walk)
		{
			void *data = walk->m_data;
			if (data != 0 && data != &g_emptyStringData)
				return array + index;
		}
	}
	return 0;
}
