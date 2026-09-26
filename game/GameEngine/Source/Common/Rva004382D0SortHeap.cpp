// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct S4SortElem8 { int m_a; int m_b; };
struct Rva004382D0Cmp
{
	bool operator()(const S4SortElem8& left, const S4SortElem8& right) const;
};
template void _STL::sort_heap<S4SortElem8*, Rva004382D0Cmp>(S4SortElem8*, S4SortElem8*, Rva004382D0Cmp);
