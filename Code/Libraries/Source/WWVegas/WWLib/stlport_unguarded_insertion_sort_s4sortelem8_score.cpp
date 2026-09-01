// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_insertion_sort_aux<S4SortElem8 *,
// S4SortElem8, S4Cmp00575AA0>, retail 0x00575750, 113 bytes.  The matched
// final-insertion wrapper at 0x00576FF0 calls this body through ILT 0x000046FB.

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
inline void __unguarded_linear_insert(RandomAccessIter last, Tp val,
	Compare comp)
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

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, *i, comp);
}

template void __unguarded_insertion_sort_aux<S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *,
	S4Cmp00575AA0);

}
