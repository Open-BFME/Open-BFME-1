// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__median<int, Q4Sort003D15A0>, retail 0x003CC370, 173
// bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// STLport's three-way median with the comparator inlined at each of its up-to
// five comparison sites, which is where the 173 bytes go. The comparator is
// the same one the partition at 0x003CE380 already fixed: the ints are
// pointers, ordered descending on the dword at +0x30 and ascending on the
// signed byte at +0x39 when those tie.
//
// The comparator's two locals are declared right operand first. That is the
// only way the loads come out in retail's order here: written left first, as
// the partition at 0x003CE380 has them, this body reads the wrong argument
// first and nothing else changes.

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

template <class Tp, class Compare>
const Tp &__median(const Tp &a, const Tp &b, const Tp &c, Compare comp)
{
	if (comp(a, b))
		if (comp(b, c))
			return b;
		else if (comp(a, c))
			return c;
		else
			return a;
	else if (comp(a, c))
		return a;
	else if (comp(b, c))
		return c;
	else
		return b;
}

template const int &__median<int, Q4Sort003D15A0>(const int &, const int &,
	const int &, Q4Sort003D15A0);

}
