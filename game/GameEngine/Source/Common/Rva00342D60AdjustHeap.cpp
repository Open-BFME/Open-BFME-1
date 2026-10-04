// cl: /DNDEBUG /MD /EHsc

// STLport's comparator overload of __adjust_heap for a four-byte scalar.
// The caller and callee grid fixes the five-argument ABI; the comparator's
// implementation is deliberately out of line, as it is in the retail body.

// Retail reaches the comparator through the ILT thunk at 0x00024B81, which
// targets the shared comparator body at 0x0033D5E0 (Q4Sort0034BFC0).
extern void j_00024b81();
// ...and the push-heap call goes through the ILT thunk at 0x00035A35.
extern void j_00035a35();

struct Q4Cmp00344A60
{
	bool operator()(int left, int right) const;
};

typedef bool (Q4Cmp00344A60::*Q4Cmp00344A60Call)(int, int) const;

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
			union { void (*raw)(void); Q4Cmp00344A60Call member; } call;
			call.raw = j_00024b81;
			if ((reinterpret_cast<const Q4Cmp00344A60 *>(&compare)->*call.member)(
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
			j_00035a35)(first, holeIndex, topIndex, value, compare);
	}

	template void __adjust_heap<int *, int, int, Q4Cmp00344A60>(
		int *, int, int, int, Q4Cmp00344A60);
}
