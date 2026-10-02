// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: STLport __partial_sort over four-byte AsciiString elements at
// retail 0x009CD980 (243 bytes), reached by the named Q3 introsort caller at
// 0x009CDAA0. The heap and sort helpers are the matched VOU family at
// 0x009CD5E0 (__make_heap, which also takes the null type and distance tags),
// 0x009CD560 and 0x009CD910. The comparator moves underscore-prefixed names in
// reverse case-insensitive order and all other names in forward order; the
// first comparison stays an out-of-line call through the 0x00027471 thunk and
// the second is inlined, as MSVC decides for one inline compareNoCase.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

template <>
inline int StringBase<char>::compareNoCase(const char *str, int len) const
{
	int myLen = m_data ? m_data->length : 0;
	const char *data = m_data ? &m_data->data[0] : "";
	int result = _memicmp(data, str, myLen < len ? myLen : len);
	if (result != 0)
		return result;
	return myLen - len;
}

template <>
inline int StringBase<char>::compareNoCase(const StringBase<char> &str) const
{
	int len = str.m_data ? str.m_data->length : 0;
	const char *data = str.m_data ? &str.m_data->data[0] : "";
	return compareNoCase(data, len);
}

struct Q3SortElem4
{
	AsciiString m_base;
};

// Stateless: the matched heap helpers it is forwarded to (BfmeStepVOU.cpp)
// build their own comparator and never read the argument. Only an empty
// comparator reproduces retail's register reload order after the inlined
// compare.
struct Q3SortCompare
{
};

struct BfmeElemVOU
{
	AsciiString m_base;
};

void q3MakeHeap(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare compare, Q3SortElem4 *, int *);
void bfmePopHeapVOU(BfmeElemVOU *first, BfmeElemVOU *last,
	BfmeElemVOU *result, BfmeElemVOU value, void *compare, int *);
void bfmeSortVOU(void *first, void *last, void *compare);

void Gen009CD980(Q3SortElem4 *first, Q3SortElem4 *middle,
	Q3SortElem4 *last, Q3SortElem4 *, Q3SortCompare compare)
{
	q3MakeHeap(first, middle, compare, (Q3SortElem4 *)0, (int *)0);
	for (Q3SortElem4 *i = middle; i < last; ++i)
	{
		bool shouldPop;
		if (i->m_base.str()[0] == '_' && first->m_base.str()[0] == '_')
			shouldPop = i->m_base.compareNoCase(first->m_base) > 0;
		else
			shouldPop = i->m_base.compareNoCase(first->m_base) < 0;
		if (shouldPop)
		{
			bfmePopHeapVOU((BfmeElemVOU *)first, (BfmeElemVOU *)middle,
				(BfmeElemVOU *)i, *(BfmeElemVOU *)i,
				*(void **)&compare, (int *)0);
		}
	}
	bfmeSortVOU(first, middle, *(void **)&compare);
}

// 0x009CDA80 (31 bytes), directly before the named Q3 introsort caller at
// 0x009CDAA0: the STLport partial_sort(first, middle, last, comp) wrapper
// shape, forwarding to __partial_sort above with a null value-type tag.  It
// sat in an unclaimed gap (16-aligned after int3 padding, ret then int3) and
// nothing calls it, so the instantiation is not witnessed: address name.
void Rva009CDA80PartialSort(Q3SortElem4 *first, Q3SortElem4 *middle,
	Q3SortElem4 *last, Q3SortCompare compare)
{
	Gen009CD980(first, middle, last, 0, compare);
}
