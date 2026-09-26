// cl: /DNDEBUG /MD /EHsc

// STLport's comparator overload of __adjust_heap for a four-byte scalar.
// The caller and callee grid fixes the five-argument ABI; the comparator's
// implementation is deliberately out of line, as it is in the retail body.

struct Q4Cmp00344A60
{
	bool operator()(int left, int right) const;
};

namespace _STL
{
	template <class RandomAccessIterator, class Distance, class Tp, class Compare>
	void __push_heap(RandomAccessIterator first, Distance holeIndex,
		Distance topIndex, Tp value, Compare compare);

	template <class RandomAccessIterator, class Distance, class Tp, class Compare>
	void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance length, Tp value, Compare compare)
	{
		Distance topIndex = holeIndex;
		Distance secondChild = 2 * holeIndex + 2;
		while (secondChild < length)
		{
			if (compare(*(first + secondChild),
				*(first + (secondChild - 1))))
			{
				--secondChild;
			}
			*(first + holeIndex) = *(first + secondChild);
			holeIndex = secondChild;
			secondChild = 2 * (secondChild + 1);
		}
		if (secondChild == length)
		{
			*(first + holeIndex) = *(first + (secondChild - 1));
			holeIndex = secondChild - 1;
		}
		__push_heap(first, holeIndex, topIndex, value, compare);
	}

	template void __adjust_heap<int *, int, int, Q4Cmp00344A60>(
		int *, int, int, int, Q4Cmp00344A60);
}
