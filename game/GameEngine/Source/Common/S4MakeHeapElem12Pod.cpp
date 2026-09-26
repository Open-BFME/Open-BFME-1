// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __make_heap over a trivially-copyable twelve-byte
// element, retail 0x00531B20, 148 bytes.  Same countdown as gen00531C50 but
// the value is three dword copies instead of a string copy constructor.

struct S4SortElem12Pod
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void bfmeAdjustHeap00531B20(S4SortElem12Pod *first, int holeIndex, int len,
	S4SortElem12Pod value, void *comp);

void gen00531B20(void *a, void *b, void *c, int, int)
{
	S4SortElem12Pod *first = (S4SortElem12Pod *)a;
	S4SortElem12Pod *last = (S4SortElem12Pod *)b;
	int len = last - first;
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	for (;;)
	{
		bfmeAdjustHeap00531B20(first, parent, len, *(first + parent), c);
		if (parent == 0)
			return;
		--parent;
	}
}
