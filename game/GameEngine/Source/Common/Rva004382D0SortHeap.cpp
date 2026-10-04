// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct S4SortElem8 { int m_a; int m_b; };
struct Rva004382D0Cmp
{
	bool operator()(const S4SortElem8& left, const S4SortElem8& right) const;
};
// Retail's sort_heap calls its adjust-heap through ILT j_00028501.
extern void j_00028501();

namespace _STL
{
	typedef void (*Adjust8)(S4SortElem8 *, int, int, S4SortElem8, Rva004382D0Cmp);

	inline void popHeap(S4SortElem8 *first, S4SortElem8 *last,
		S4SortElem8 *result, S4SortElem8 value, Rva004382D0Cmp compare, int *)
	{
		*result = *first;
		((Adjust8)j_00028501)(first, 0, (int)(last - first), value, compare);
	}

	inline void popHeapAux(S4SortElem8 *first, S4SortElem8 *last,
		Rva004382D0Cmp compare)
	{
		popHeap(first, last - 1, last - 1, *(last - 1), compare, (int *)0);
	}

	template <>
	void sort_heap<S4SortElem8 *, Rva004382D0Cmp>(S4SortElem8 *first,
		S4SortElem8 *last, Rva004382D0Cmp compare)
	{
		while (last - first > 1)
			popHeapAux(first, last--, compare);
	}
}
