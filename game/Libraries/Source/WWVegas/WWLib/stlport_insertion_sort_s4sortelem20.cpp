// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: _STL::__insertion_sort<S4SortElem20 *, S4Cmp002EB8E0>, retail
// 0x002EB270, 144 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// The twenty-byte cousin of the sorts at 0x002E1170 and 0x00532080. Same
// STLport source -- the element goes to __linear_insert by value -- but this
// element has two members that need construction rather than one, so the copy
// is a string copy constructor at +0, a byte at +4, and a second out-of-line
// copy constructor for the twelve bytes at +8. The stride confirms the size:
// __i starts at first + 0x14 and advances by 0x14.
//
// Two members with destructors is also why this body has an unwind frame where
// its twelve-byte cousins have none: the state goes to 0 while the second
// member is being constructed, so the string gets destroyed if that throws.
//
// The string needs a destructor as well as a copy constructor, even though
// neither is called in this body. Without one the element is trivially
// destructible, the by-value argument needs no address recorded, and the store
// of the temporary's address into the now-dead first parameter slot -- four
// bytes -- does not appear.

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
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);	// ILT 0x000266BB
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
	AsciiString m_bfmeName;					// +0x00
	char m_bfmeFlag;					// +0x04
	BfmeSortElem20Tail m_bfmeTail;				// +0x08
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);						// ILT 0x0002D34E

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (first == last)
		return;

	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<S4SortElem20 *, S4Cmp002EB8E0>(
	S4SortElem20 *, S4SortElem20 *, S4Cmp002EB8E0);

}
