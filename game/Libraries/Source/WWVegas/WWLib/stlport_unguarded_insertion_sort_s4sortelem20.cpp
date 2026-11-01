// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: _STL::__unguarded_insertion_sort_aux<S4SortElem20 *,
// S4SortElem20, S4Cmp002EB8E0>, retail 0x002EA750.

#include "ascii_string.h"
#include <vector>

// Retail ILT 0x0000E921 routes to the vector destructor at 0x002E1260.
struct Gen002E1260;
namespace _STL
{
template <> vector<Gen002E1260>::~vector();
}

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	// Noinline: retail's S4 dtor calls this out of line through ILT 0xE921.
	// Inlining it would route the vector call direct and the S4 dtor copy
	// would no longer be retail's body.
	__declspec(noinline) ~BfmeSortElem20Tail(void)
	{
		typedef _STL::vector<Gen002E1260> RetailVector;
		reinterpret_cast<RetailVector *>(this)->~RetailVector();
	}

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	AsciiString m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, *i, comp);
}

template void __unguarded_insertion_sort_aux<S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20 *,
	S4Cmp002EB8E0);

}
