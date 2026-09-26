// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__adjust_heap<S4SortElem8 *, int, S4SortElem8,
// S4Cmp009F34B0>, retail 0x009F3190, 122 bytes. The body carried only a
// machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name with
// identity=real.
//
// STLport's sift-down verbatim. The element is eight bytes and the comparator
// is inlined into a single x87 sequence -- fld of the right child's float at
// +4, fcomp against the left child's, fnstsw and a parity test -- so the key is
// a float at +4 and the ordering is a plain less-than on it. The comparator
// itself is never read, so it is an empty struct.
//
// The element copy is two plain dword moves, which is what a POD of this size
// gives; nothing in the loop calls a copy constructor.
//
// __push_heap takes the value by value, so the tail pushes six dwords: first,
// the hole and top indices, the two halves of the element, and the comparator.

struct S4SortElem8
{
	int m_bfmeA;						// +0x00
	float m_bfmeKey;					// +0x04
};

struct S4Cmp009F34B0
{
	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey > b.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);		// retail 0x009F2F00

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			secondChild--;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp009F34B0>(
	S4SortElem8 *, int, int, S4SortElem8, S4Cmp009F34B0);

}
