// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Twin of 0x00438270 (GameTextFinalInsertionSort.cpp): same threshold-split
// final insertion sort shape over Q3SortElem8, with different sort-pass
// callees (0x002618D0 / 0x002610B0).

struct Q3SortElem8
{
	int label;
	int info;
};

struct Q3SortCompare
{
	void *state;
};

void b_002618d0();
void b_002610b0();

typedef void (__cdecl *SortPass)(Q3SortElem8 *, Q3SortElem8 *, Q3SortCompare);

void Gen00261A20(Q3SortElem8 *first, Q3SortElem8 *last, Q3SortCompare comp)
{
	if (last - first > 16)
	{
		((SortPass)b_002618d0)(first, first + 16, comp);
		((SortPass)b_002610b0)(first + 16, last, comp);
	}
	else
	{
		((SortPass)b_002618d0)(first, last, comp);
	}
}
