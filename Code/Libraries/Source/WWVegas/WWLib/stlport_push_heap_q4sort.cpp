// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__push_heap<int *, int, int, Q4Sort003D15A0>, retail
// 0x003CC5F0, 103 bytes. The body carried only a machine byte-dump row.
//
// STLport's sift-up with the same comparator the median at 0x003CC370 and
// the partition at 0x003CE380 already fixed: the ints are pointers, ordered
// descending on the dword at +0x30 and ascending on the signed byte at +0x39
// when those tie. The comparator locals are declared left operand first, as
// the partition has them.

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
		const BfmeQ4SortKey *x = (const BfmeQ4SortKey *)a;
		const BfmeQ4SortKey *y = (const BfmeQ4SortKey *)b;

		if (x->m_bfmeRank > y->m_bfmeRank)
			return true;
		if (x->m_bfmeRank < y->m_bfmeRank)
			return false;
		return x->m_bfmeTie < y->m_bfmeTie;
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

template void __push_heap<int *, int, int, Q4Sort003D15A0>(
	int *, int, int, int, Q4Sort003D15A0);

}
