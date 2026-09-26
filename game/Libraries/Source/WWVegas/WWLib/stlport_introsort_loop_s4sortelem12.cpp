// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: _STL::__introsort_loop<S4SortElem12 *, S4SortElem12, int,
// S4Cmp00574DF0>, retail 0x00575320, 240 bytes.  Same 12-byte element and
// first-field comparator as the matched __final_insertion_sort at 0x00574DF0
// and __linear_insert at 0x00573900.  Median-of-3 is inlined as signed
// compares of m_bfmeKey; the three REL32s are unguarded_partition,
// this body, and __partial_sort.

#include <algorithm>

struct S4SortElem12
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00574DF0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeKey < right.m_bfmeKey;
	}
};

namespace _STL
{

template void __introsort_loop<S4SortElem12 *, S4SortElem12, int,
	S4Cmp00574DF0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *, int,
	S4Cmp00574DF0);

}
