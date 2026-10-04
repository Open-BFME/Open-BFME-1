// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

struct BfmeQ4SortKey
{
	char m_bfmeHead[0x30];
	int m_bfmeRank;
	char m_bfmeMid[0x39 - 0x34];
	char m_bfmeTie;
};

struct Q4Sort003D15A0
{
	bool operator()(int a, int b) const
	{
		const BfmeQ4SortKey *y = (const BfmeQ4SortKey *)b;
		const BfmeQ4SortKey *x = (const BfmeQ4SortKey *)a;

		if (x->m_bfmeRank > y->m_bfmeRank)
			return true;
		if (x->m_bfmeRank < y->m_bfmeRank)
			return false;
		return x->m_bfmeTie < y->m_bfmeTie;
	}
};

// Retail's sort_heap sifts down through the already-landed __adjust_heap at
// 0x003CDD00 (stlport_adjust_heap_q4sort.cpp owns it, __push_heap tail
// included). Declaring the specialization keeps this TU from instantiating its
// own __adjust_heap/__push_heap COMDAT copies, which are not retail's bodies.
namespace _STL
{
template <>
void __adjust_heap<int *, int, int, Q4Sort003D15A0>(int *, int, int, int, Q4Sort003D15A0);
}

template void _STL::sort_heap<int *, Q4Sort003D15A0>(int *, int *, Q4Sort003D15A0);
