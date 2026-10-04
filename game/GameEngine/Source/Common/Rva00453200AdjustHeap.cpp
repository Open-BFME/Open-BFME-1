// cl: /DNDEBUG /MD /EHsc

// STLport's comparator overload of __adjust_heap for a four-byte scalar.
// twin of ??$__adjust_heap@PAHHHUQ4Cmp00344A60@@@_STL@@YAXPAHHHHUQ4Cmp00344A60@@@Z
// (retail 0x00342D60, game/GameEngine/Source/Common/Rva00342D60AdjustHeap.cpp).
// Retail's compare call routes through ILT 0x00024055 to the existing
// Q4Sort004566F0 operator() body at RVA 0x00451F60.

// Retail calls the comparator through ILT 0x00024055 and push_heap through ILT
// 0x000190C4 (-> 0x004529D0).
extern void j_00024055();
extern void j_000190c4();

struct Q4Sort004566F0
{
	bool operator()(int left, int right) const;
};

typedef bool (Q4Sort004566F0::*Q4Sort004566F0Call)(int, int) const;

// Keep the heap template identity while binding its stateless call to the
// one existing comparator provider; the empty base needs no this adjustment.
struct Q4Cmp00453BB0 : Q4Sort004566F0
{
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
			union { void (*raw)(void); Q4Sort004566F0Call member; } call;
			call.raw = j_00024055;
			if ((reinterpret_cast<const Q4Sort004566F0 *>(&compare)->*call.member)(
				*(first + secondChild), *(first + (secondChild - 1))))
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
		((void (*)(RandomAccessIterator, Distance, Distance, Tp, Compare))
			j_000190c4)(first, holeIndex, topIndex, value, compare);
	}

	template void __adjust_heap<int *, int, int, Q4Cmp00453BB0>(
		int *, int, int, int, Q4Cmp00453BB0);
}
