// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__push_heap<S4SortElem8 *, int, S4SortElem8,
// S4Cmp00575AA0>, retail 0x00574FC0, 104 bytes.  Its matched __adjust_heap
// caller proves the specialization and the comparator's direct ILT target.

struct S4SortElem8
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool BfmeLess00574AA0(const S4SortElem8 &other) const;
};

struct S4Cmp00575AA0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &left,
		const S4SortElem8 &right) const
	{
		return left.BfmeLess00574AA0(right);
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

template void __push_heap<S4SortElem8 *, int, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, int, int, S4SortElem8, S4Cmp00575AA0);

}
