// ?Gen00754430@@YAXPAUQ3SortElem4@@0UQ3SortCompare@@@Z
// partial score=0.99 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /FAsc /Fa build/candidate_00754430.cod
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

struct Q3SortElem4
{
	int m_value;
};

struct BfmeCompAR
{
	bool operator()(int left, int right);
	int m_state;
};

struct Q3SortCompare : BfmeCompAR
{
};

extern void bfmeUnguardedInsertAR(int *last, int value, BfmeCompAR comp);

extern "C" __declspec(dllimport) void * __cdecl memmove(
	void *destination, const void *source, unsigned int bytes);

void Gen00754430(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare comp)
{
	if (first != last)
	{
		Q3SortElem4 *cursor = first + 1;
		while (cursor != last)
		{
			int value = cursor->m_value;
			if (comp(value, first->m_value))
			{
				unsigned int bytes = (char *)cursor - (char *)first;
				if ((int)bytes > 0)
					memmove((char *)(cursor + 1) - bytes, first, bytes);
				first->m_value = value;
			}
			else
			{
				bfmeUnguardedInsertAR((int *)cursor, value, *(BfmeCompAR *)&comp);
			}
			++cursor;
		}
	}
}
