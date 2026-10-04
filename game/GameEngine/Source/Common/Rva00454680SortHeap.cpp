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

template void _STL::sort_heap<int *, Q4Cmp00453BB0>(int *, int *, Q4Cmp00453BB0);
