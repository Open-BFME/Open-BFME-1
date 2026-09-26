// STLport sort_heap over int with the comparator whose adjust_heap body is
// matched at retail 0x007538A0.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

struct Q4Cmp00753DD0
{
	bool operator()(int left, int right) const;
};

template void _STL::sort_heap<int *, Q4Cmp00753DD0>(
	int *, int *, Q4Cmp00753DD0);
