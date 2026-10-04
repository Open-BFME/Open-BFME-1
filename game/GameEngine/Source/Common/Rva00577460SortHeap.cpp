// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct S4SortElem8 { int m_a; int m_b; };
struct Rva00577460Cmp
{
	bool operator()(const S4SortElem8& left, const S4SortElem8& right) const;
};
// Retail's sort_heap calls its adjust-heap through ILT j_00027138.
extern void j_00027138();

namespace _STL
{
	typedef void (*Adjust8)(S4SortElem8 *, int, int, S4SortElem8, Rva00577460Cmp);

	inline void popHeap(S4SortElem8 *first, S4SortElem8 *last,
		S4SortElem8 *result, S4SortElem8 value, Rva00577460Cmp compare, int *)
	{
		*result = *first;
		((Adjust8)j_00027138)(first, 0, (int)(last - first), value, compare);
	}

	inline void popHeapAux(S4SortElem8 *first, S4SortElem8 *last,
		Rva00577460Cmp compare)
	{
		popHeap(first, last - 1, last - 1, *(last - 1), compare, (int *)0);
	}

	template <>
	void sort_heap<S4SortElem8 *, Rva00577460Cmp>(S4SortElem8 *first,
		S4SortElem8 *last, Rva00577460Cmp compare)
	{
		while (last - first > 1)
			popHeapAux(first, last--, compare);
	}
}
