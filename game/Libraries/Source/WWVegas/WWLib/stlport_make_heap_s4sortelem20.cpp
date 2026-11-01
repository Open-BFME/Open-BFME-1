// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME: _STL::__make_heap<S4SortElem20 *, S4Cmp002EB8E0,
// S4SortElem20, int>, retail 0x002EACD0, 184 bytes.  The neighboring
// STLport sort bodies identify the twenty-byte element and comparator.

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

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *)
{
	Distance len = last - first;
	if (len < 2)
		return;
	Distance parent = (len - 2) / 2;
	for (;;)
	{
		__adjust_heap(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}

template void __make_heap<S4SortElem20 *, S4Cmp002EB8E0,
	S4SortElem20, int>(S4SortElem20 *, S4SortElem20 *, S4Cmp002EB8E0,
	S4SortElem20 *, int *);

}
