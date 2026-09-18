// ?Gen00754430@@YAXPAUQ3SortElem4@@0UQ3SortCompare@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /FAsc /Fa build/Q3InsertionSort00754430.cod
// stlport

struct Q3SortElem4
{
	int m_value;
};

class BfmeCompAR
{
	public:
	__declspec(noinline) bool operator()(int left, int right)
	{
		return left < right;
	}
	int m_state;
};

struct Q3SortCompare
{
	void *m_state;
};

extern void bfmeUnguardedInsertAR(int *last, int value, BfmeCompAR comp);

extern "C" __declspec(dllimport) void * __cdecl memmove(
	void *destination, const void *source, unsigned int bytes);

__forceinline int *bfmeCopyBackward(int *first, int *last, int *result)
{
	int bytes = (char *)last - (char *)first;
	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);
	return (int *)((char *)result - bytes);
}

__forceinline void bfmeLinearInsertARVariant(int *first, int *last, int value,
	BfmeCompAR comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);
		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAR(last, value, comp);
	}
}

void Gen00754430(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare comp)
{
	int *rawFirst = (int *)first;
	int *rawLast = (int *)last;
	if (rawFirst == rawLast)
		return;
	for (int *i = rawFirst + 1; i != rawLast; ++i)
		bfmeLinearInsertARVariant(rawFirst, i, *i, *(BfmeCompAR *)&comp);
}
