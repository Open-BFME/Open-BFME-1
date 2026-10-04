// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

struct Q4Sort004566F0
{
	bool operator()(int left, int right) const;
};

// Keep the heap template identity while binding its stateless call to the
// one existing comparator provider; the empty base needs no this adjustment.
struct Q4Cmp00453BB0 : Q4Sort004566F0
{
};

// The adjust-heap body is retail's own (Rva00453200AdjustHeap.cpp); declare the
// specialization so this TU emits no comparator-calling copy of it.
namespace _STL
{
	template <>
	void __adjust_heap<int *, int, int, Q4Cmp00453BB0>(
		int *, int, int, int, Q4Cmp00453BB0);
}

template void _STL::sort_heap<int *, Q4Cmp00453BB0>(int *, int *, Q4Cmp00453BB0);
