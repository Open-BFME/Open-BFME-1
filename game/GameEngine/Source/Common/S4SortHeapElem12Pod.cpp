// cl: /DNDEBUG /MD /EHsc

// STLport sort_heap over the twelve-byte pointer-key-int record.
// Retail calls the matched adjust_heap at 0x005300E0 through 0x0001D0B6.

struct S4Named0052E880;

struct S4SortElem12
{
	S4Named0052E880 *m_bfmeObj;
	int m_bfmeKey;
	int m_bfmeThird;
};

void bfmeAdjustHeap005300E0(S4SortElem12 *first, int holeIndex, int len,
	S4SortElem12 value, void *comp);

void gen005327C0(void *firstVoid, void *lastVoid, void *comp)
{
	char *first = (char *)firstVoid;
	char *last = (char *)lastVoid;

	while ((last - first) / 12 > 1)
	{
		S4SortElem12 val = *(S4SortElem12 *)(last - 12);
		*(S4SortElem12 *)(last - 12) = *(S4SortElem12 *)first;
		bfmeAdjustHeap005300E0((S4SortElem12 *)first, 0,
			(int)((last - 12 - first) / 12), val, comp);
		last -= 12;
	}
}
