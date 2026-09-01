// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_linear_insert<S4SortElem8 *,
// S4SortElem8, S4Cmp00575AA0>, retail 0x00574F60, 68 bytes.  Its exact
// __linear_insert caller at 0x005756C0 reaches this specialization through
// ILT 0x0002DB3C and fixes the element, comparator, and by-value layout.

struct S4SortElem8
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool BfmeLess00574AA0(const S4SortElem8 &other) const;
};

struct S4Cmp00575AA0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &left,
		const S4SortElem8 &right) const
	{
		return left.BfmeLess00574AA0(right);
	}
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
	RandomAccessIter next = last;
	--next;
	while (comp(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

template void __unguarded_linear_insert<S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, S4SortElem8, S4Cmp00575AA0);

}
