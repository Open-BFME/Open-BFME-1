// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Final insertion-sort pass used for BFME's eight-byte StringLookUp records.

struct Q3SortElem8
{
	int label;
	int info;
};

struct Q3SortCompare
{
	void *state;
};

void b_00437e90();
void b_00437c40();

typedef void (__cdecl *SortPass)(Q3SortElem8 *, Q3SortElem8 *, Q3SortCompare);

void Gen00438270(Q3SortElem8 *first, Q3SortElem8 *last, Q3SortCompare comp)
{
	if (last - first > 16)
	{
		((SortPass)b_00437e90)(first, first + 16, comp);
		((SortPass)b_00437c40)(first + 16, last, comp);
	}
	else
	{
		((SortPass)b_00437e90)(first, last, comp);
	}
}
