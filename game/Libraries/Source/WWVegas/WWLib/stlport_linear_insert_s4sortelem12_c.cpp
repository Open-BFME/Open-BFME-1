// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__linear_insert<S4SortElem12 *, S4SortElem12,
// S4Cmp00574DF0>, retail 0x00573900, 102 bytes.  Its matched insertion-sort
// caller at 0x00574250 proves the specialization; both helper targets are
// decoded from this body's direct ILT calls.

struct S4SortElem12
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00574DF0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeKey < right.m_bfmeKey;
	}
};

namespace _STL
{

struct random_access_iterator_tag
{
};

S4SortElem12 *BfmeCopyBackward00570F50(S4SortElem12 *first,
	S4SortElem12 *last, S4SortElem12 *result,
	const random_access_iterator_tag &tag, int *distance);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first,
	RandomAccessIter last, Tp val, Compare comp)
{
	if (comp(val, *first))
	{
		random_access_iterator_tag tag;
		BfmeCopyBackward00570F50(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem12 *, S4SortElem12,
	S4Cmp00574DF0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp00574DF0);

}
