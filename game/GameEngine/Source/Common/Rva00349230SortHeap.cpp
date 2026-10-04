// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

struct Q4Cmp00344A60
{
	bool operator()(int left, int right) const;
};

// The adjust-heap body is retail's own (Rva00342D60AdjustHeap.cpp); declare the
// specialization so this TU emits no comparator-calling copy of it.
namespace _STL
{
	template <>
	void __adjust_heap<int *, int, int, Q4Cmp00344A60>(
		int *, int, int, int, Q4Cmp00344A60);
}

template void _STL::sort_heap<int *, Q4Cmp00344A60>(int *, int *, Q4Cmp00344A60);
