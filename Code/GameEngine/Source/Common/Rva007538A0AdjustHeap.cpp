// cl: /DNDEBUG /MD /EHsc

// Byte-twin of ??$__adjust_heap@PAHHHUQ4Cmp00344A60@@@_STL@@YAXPAHHHHUQ4Cmp00344A60@@@Z
// at 0x00342D60 (Rva00342D60AdjustHeap.cpp): identical 113 bytes once
// relocations are masked. The comparator callee (0x0002952D) is still a
// dump; only its thunk address is pinned here.

struct Q4Cmp00753DD0
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

	template void __adjust_heap<int *, int, int, Q4Cmp00753DD0>(
		int *, int, int, int, Q4Cmp00753DD0);
}
