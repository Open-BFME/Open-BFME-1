// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__partial_sort<int *, int, Q4Sort003D15A0>, retail
// 0x003D00E0, 135 bytes. The body carried only a machine byte-dump row;
// reverse/symbols.csv holds the name.
//
// STLport's heap-select: __make_heap the [first, middle) range, then for each
// later element pop it onto the heap when it is less than the front, then
// sort_heap. The comparator is the same one the median, partition and
// push_heap already fixed -- ints are pointers, descending on +0x30 and
// ascending on the signed byte at +0x39.

struct BfmeQ4SortKey
{
	char m_bfmeHead[0x30];
	int m_bfmeRank;						// +0x30
	char m_bfmeMid[0x39 - 0x34];
	char m_bfmeTie;						// +0x39
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
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last, Tp *, Compare comp)
{
	__make_heap(first, middle, comp, (Tp *)0, (int *)0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		Tp front = *first;
		Tp item = *i;
		if (comp(item, front))
		{
			*i = front;
			__adjust_heap(first, 0, (int)(middle - first), item, comp);
		}
	}
	sort_heap(first, middle, comp);
}

template void __partial_sort<int *, int, Q4Sort003D15A0>(
	int *, int *, int *, int *, Q4Sort003D15A0);

}
