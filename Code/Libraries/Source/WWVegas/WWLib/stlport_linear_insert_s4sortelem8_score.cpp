// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__linear_insert<S4SortElem8 *, S4SortElem8,
// S4Cmp00575AA0>, retail 0x005756C0, 114 bytes.  The body calls the same
// score comparator as the adjacent matched sort helpers and hands its
// unguarded arm through ILT 0x0002DB3C to retail 0x00574F60.

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

struct random_access_iterator_tag
{
};

template <class RandomAccessIter, class BidirectionalIter, class Distance>
__forceinline BidirectionalIter __copy_backward(RandomAccessIter first,
	RandomAccessIter last, BidirectionalIter result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count)
		*--result = *--last;
	return result;
}

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp)
{
	if (comp(val, *first))
	{
		random_access_iterator_tag tag;
		__copy_backward(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0);

}
