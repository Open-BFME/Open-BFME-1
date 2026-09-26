// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__push_heap<S4SortElem8 *, int, S4SortElem8,
// S4Cmp009F3400>, retail 0x009F2E90, 96 bytes. The body carried only a
// machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name with
// identity=real.
//
// STLport's sift-up, and the callee the sift-down at 0x009F3110 tails into.
// Same eight-byte element and same inlined comparator: fld of the parent's
// float at +4, fcomp against the by-value element on the stack, fnstsw and a
// status test against 5, so the ordering is a less-than on that float.
//
// The value arrives by value, which is why the comparison reads it from the
// frame rather than through a pointer, and the final store writes it back into
// the array.

struct S4SortElem8
{
	int m_bfmeA;						// +0x00
	float m_bfmeKey;					// +0x04
};

struct S4Cmp009F3400
{
	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), val))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp009F3400>(
	S4SortElem8 *, int, int, S4SortElem8, S4Cmp009F3400);

}
