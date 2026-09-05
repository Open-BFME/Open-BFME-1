// cl: /DNDEBUG /MD /EHsc

// STLport's comparator overload of __adjust_heap for a four-byte scalar.
// twin of ??$__adjust_heap@PAHHHUQ4Cmp00344A60@@@_STL@@YAXPAHHHHUQ4Cmp00344A60@@@Z
// (retail 0x00342D60, Code/GameEngine/Source/Common/Rva00342D60AdjustHeap.cpp).
// The comparator's own operator() is out of line and ICF-folded with the
// pinned callee named BfmeCompAO (reverse/symbols.csv, 0x00024055).

struct Q4Cmp00453BB0
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

	template void __adjust_heap<int *, int, int, Q4Cmp00453BB0>(
		int *, int, int, int, Q4Cmp00453BB0);
}
