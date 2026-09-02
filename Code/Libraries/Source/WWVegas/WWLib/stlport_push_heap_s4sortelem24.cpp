// cl: /DNDEBUG /MD /EHsc
//
// _STL::push_heap over S4SortElem24 / S4Cmp009F4BF0. Inlines to a by-value
// copy of last[-1] and a call to the already-landed __push_heap at 0x009F4BF0.

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
	bool operator()(const S4SortElem24 &a, const S4SortElem24 &b) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare>
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	__push_heap(first, (int)(last - first) - 1, 0, *(last - 1), comp);
}

template void push_heap<S4SortElem24 *, S4Cmp009F4BF0>(
	S4SortElem24 *, S4SortElem24 *, S4Cmp009F4BF0);

}
