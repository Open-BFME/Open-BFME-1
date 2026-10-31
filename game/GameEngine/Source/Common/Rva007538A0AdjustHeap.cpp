// cl: /DNDEBUG /MD /EHsc

// Byte-twin of ??$__adjust_heap@PAHHHUQ4Cmp00344A60@@@_STL@@YAXPAHHHHUQ4Cmp00344A60@@@Z
// at 0x00342D60 (Rva00342D60AdjustHeap.cpp): identical 113 bytes once
// relocations are masked. The comparator callee (0x0002952D) is still a
// dump; only its thunk address is pinned here.

// Keep the existing template identity; the native comparator provider is Q4Sort.
struct Q4Cmp00753DD0 { void *m_state; };
struct Q4Sort00755050
{
    void *m_state;
    bool operator()(int left, int right) const;
};
// Retail's push step is ILT 0x00009214 -> 0x007534F0, the row defined in
// S4StlSortHelpers.cpp as __push_heap over S4Cmp007534F0 (same one-word
// comparator); this unit's own comparator spelling names nothing.
struct S4Cmp007534F0
{
    void *m_state;
    bool operator()(int, int) const;
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
			if ((*reinterpret_cast<const Q4Sort00755050 *>(&compare))(*(first + secondChild),
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
		__push_heap(first, holeIndex, topIndex, value,
			*reinterpret_cast<const S4Cmp007534F0 *>(&compare));
	}

	template void __adjust_heap<int *, int, int, Q4Cmp00753DD0>(
		int *, int, int, int, Q4Cmp00753DD0);
}
