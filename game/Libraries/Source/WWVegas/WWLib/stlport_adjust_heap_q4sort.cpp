// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__adjust_heap<int *, int, int, Q4Sort003D15A0>, retail
// 0x003CDD00, 131 bytes. The body carried only a machine byte-dump row.
//
// STLport's sift-down, and the callee the __make_heap at 0x003CE510 and the
// __partial_sort at 0x003D00E0 both reach. Same comparator as the median,
// partition and push_heap: ints are pointers, descending on +0x30 and
// ascending on the signed byte at +0x39. The tail is the already-landed
// __push_heap at 0x003CC5F0. Comparator locals are declared right operand
// first so the child loads come out in retail order.

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
		const BfmeQ4SortKey *y = (const BfmeQ4SortKey *)b;
		const BfmeQ4SortKey *x = (const BfmeQ4SortKey *)a;

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
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		Tp left = *(first + (secondChild - 1));
		Tp right = *(first + secondChild);
		if (comp(right, left))
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

template void __adjust_heap<int *, int, int, Q4Sort003D15A0>(
	int *, int, int, int, Q4Sort003D15A0);

}
