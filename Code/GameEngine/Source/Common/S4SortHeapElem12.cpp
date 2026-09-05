// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport sort_heap over a twelve-byte element, retail
// 0x00573A30.  The 0x2AAAAAAB multiply is (last-first)/12.  pop_heap is
// inlined; the out-of-line callee is the 12-byte __adjust_heap at
// 0x00571B70 (ILT 0x0003DF00).  Element/comparator identity beyond width
// is not recovered -- S4SortElem12 is the same stand-in the neighbouring
// linear_insert at 0x00573900 uses.

struct S4SortElem12
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00573A30
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const { return left.m_bfmeKey < right.m_bfmeKey; }
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp)
{
	while (last - first > 1)
	{
		S4SortElem12 val = *(last - 1);
		*(last - 1) = *first;
		__adjust_heap(first, 0, (last - 1) - first, val, comp);
		--last;
	}
}

template void sort_heap<S4SortElem12 *, S4Cmp00573A30>(
	S4SortElem12 *, S4SortElem12 *, S4Cmp00573A30);

}
