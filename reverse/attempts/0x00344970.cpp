// ?Gen00344970@@YAXPAUQ3SortElem4@@0UQ3SortCompare@@@Z
// partial score=0.95 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

extern "C" __declspec(dllimport) void * __cdecl memmove(
	void *destination, const void *source, unsigned int bytes);

struct Q4Sort0034BFC0
{
	bool operator()(int left, int right) const;
};

struct Q3SortElem4
{
	int m_value;
};

struct Q3SortCompare
{
	bool operator()(Q3SortElem4 left, Q3SortElem4 right) const
	{
		return ((const Q4Sort0034BFC0 *)this)->operator()(
			left.m_value, right.m_value);
	}
};

struct BfmeInsertCompareA
{
	void *m_state;
	bool operator()(void *pending, void *element);
};

extern void bfmeLinearInsert_00340860(
	void **last, void *pending, BfmeInsertCompareA compare);

__forceinline Q3SortElem4 *q3CopyBackward(
	Q3SortElem4 *result, Q3SortElem4 *first, Q3SortElem4 *last)
{
	int bytes = (char *)last - (char *)first;
	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);
	return (Q3SortElem4 *)((char *)result - bytes);
}

void Gen00344970(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare comp)
{
	if (first == last)
		return;

	for (Q3SortElem4 *i = first + 1; i != last; ++i)
	{
		Q3SortElem4 value = *i;
		if (comp(value, *first))
		{
			q3CopyBackward(i + 1, first, i);
			*first = value;
		}
		else
		{
			bfmeLinearInsert_00340860(
				(void **)i, (void *)value.m_value,
				*(BfmeInsertCompareA *)&comp);
		}
	}
}
