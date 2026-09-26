// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__partial_sort<S4SortElem8 *, S4SortElem8,
// S4Cmp00575AA0>, retail 0x00577690, 124 bytes.  STLport carries the type and
// distance tags as null arguments, while the comparison is the element member
// used by the surrounding score sort family.

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

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp);

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first,
	RandomAccessIterator middle, RandomAccessIterator last, Tp *,
	Compare comp)
{
	__make_heap(first, middle, comp, (Tp *)0, (int *)0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			Tp item = *i;
			*i = *first;
			__adjust_heap(first, 0, (int)(middle - first), item, comp);
		}
	}
	sort_heap(first, middle, comp);
}

template void __partial_sort<S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *,
	S4SortElem8 *, S4Cmp00575AA0);

}
