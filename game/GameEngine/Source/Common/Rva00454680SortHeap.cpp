// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

struct Q4Cmp00453BB0
{
	bool operator()(int left, int right) const;
};

template void _STL::sort_heap<int *, Q4Cmp00453BB0>(int *, int *, Q4Cmp00453BB0);
