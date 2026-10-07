// cl: /DNDEBUG /MD /EHsc

// STLport make_heap over the twelve-byte pointer-key-int record.
// Retail calls the matched adjust_heap at 0x005300E0 through 0x0001D0B6.

struct S4Named0052E880;

struct S4SortElem12
{
	S4Named0052E880 *m_bfmeObj;
	int m_bfmeKey;
	int m_bfmeThird;
};

void __adjust_heap(S4SortElem12 *first, int holeIndex, int len,
	S4SortElem12 value, void *comp);

void gen00531B20(void *a, void *b, void *c, int, int)
{
	S4SortElem12 *first = (S4SortElem12 *)a;
	S4SortElem12 *last = (S4SortElem12 *)b;
	int len = last - first;
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	for (;;)
	{
		__adjust_heap(first, parent, len, *(first + parent), c);
		if (parent == 0)
			return;
		--parent;
	}
}
