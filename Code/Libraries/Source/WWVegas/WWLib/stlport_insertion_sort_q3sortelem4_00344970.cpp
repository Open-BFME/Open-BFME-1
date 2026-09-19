// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

// The caller in Q3IntrosortFamilies.cpp uses this STLport insertion sort
// for four-byte elements.  Retail calls Q4Sort0034BFC0 for the guarded
// comparison and then calls the shared linear-insert helper for the other
// branch.

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
		Q4Sort0034BFC0 &compare = *(Q4Sort0034BFC0 *)&last;
		if (compare(value.m_value, first->m_value))
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
