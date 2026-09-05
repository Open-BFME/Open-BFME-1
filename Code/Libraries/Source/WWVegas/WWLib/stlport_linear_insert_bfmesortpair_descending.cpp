// cl: /DNDEBUG /MD /EHsc

// Near-twin of stlport_linear_insert_s4sortelem8_score.cpp's
// __linear_insert<S4SortElem8 *, S4SortElem8, S4Cmp00575AA0> (retail
// 0x005756C0), sibling of stlport_linear_insert_bfmesortpair_ascending.cpp
// (retail 0x009F3830). Same shape, descending comparator: comp(val, *first)
// is a plain float compare (m_key >), and the unguarded arm routes to the
// already-matched bfmeLinearInsertFloatDescending (BfmeLinearInsertFloat.cpp,
// retail 0x009F2E30).

struct BfmeSortPair
{
	unsigned int m_value;
	float m_key;
};

struct BfmeSortCompareDescending
{
	bool operator()(const BfmeSortPair &left, const BfmeSortPair &right) const
	{
		return left.m_key > right.m_key;
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

template void __linear_insert<BfmeSortPair *, BfmeSortPair,
	BfmeSortCompareDescending>(BfmeSortPair *, BfmeSortPair *, BfmeSortPair,
	BfmeSortCompareDescending);

}
