// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<int *, int, Q4Sort003D15A0>, retail
// 0x003CE380, 100 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// STLport's partition loop verbatim. The element type is int, but the values
// are pointers: every comparison dereferences them, reading a dword at +0x30
// and a signed byte at +0x39 of whatever they point at.
//
// The comparator that shape implies is a two-key ordering -- descending on the
// dword, and on a tie ascending on the byte. Both directions are visible: the
// first inner loop advances while (*first)->+0x30 is greater than the pivot's,
// the second retreats while the pivot's is greater than (*last)'s, and each
// falls through to the byte compare only when the dwords are equal.
//
// The comparator is passed by value and never read, so it is an empty struct.
// The pivot's dword is reloaded at the top of each outer pass rather than kept,
// because the swap may have moved what it points at.

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

template <class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 a, ForwardIter2 b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template int *__unguarded_partition<int *, int, Q4Sort003D15A0>(int *, int *, int, Q4Sort003D15A0);

}
