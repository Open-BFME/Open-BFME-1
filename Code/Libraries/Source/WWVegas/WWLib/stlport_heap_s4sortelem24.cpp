// cl: /DNDEBUG /MD /EHsc

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
	bool operator()(const S4SortElem24 &a, const S4SortElem24 &b) const
	{
		return a.m_key < b.m_key;
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

template void __push_heap<S4SortElem24 *, int, S4SortElem24, S4Cmp009F4BF0>(
	S4SortElem24 *, int, int, S4SortElem24, S4Cmp009F4BF0);

template void __adjust_heap<S4SortElem24 *, int, S4SortElem24, S4Cmp009F4BF0>(
	S4SortElem24 *, int, int, S4SortElem24, S4Cmp009F4BF0);

}
