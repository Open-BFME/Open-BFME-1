// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__partial_sort<S4SortElem12 *, S4SortElem12,
// S4Cmp00574DF0>, retail 0x00574330, 176 bytes.  Zero-fourth forwarder
// callee of rva00574EE0.  Inlined m_bfmeKey compare; 12-byte records.

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

template void __partial_sort<S4SortElem12 *, S4SortElem12,
	S4Cmp00574DF0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *,
	S4SortElem12 *, S4Cmp00574DF0);

}
