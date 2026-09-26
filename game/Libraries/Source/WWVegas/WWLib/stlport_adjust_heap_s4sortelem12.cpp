// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__adjust_heap<S4SortElem12 *, int, S4SortElem12,
// S4Cmp00574DF0>, retail 0x00571B70, 166 bytes.  Inlined m_bfmeKey compare;
// tails into the landed 12-byte push-heap at 0x00570DE0 through ILT 0x0001F325.
// Same element and comparator as the exact linear-insert at 0x00573900.

struct S4SortElem12
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00574DF0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeKey < right.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

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

template void __adjust_heap<S4SortElem12 *, int, S4SortElem12,
	S4Cmp00574DF0>(S4SortElem12 *, int, int, S4SortElem12, S4Cmp00574DF0);

}
