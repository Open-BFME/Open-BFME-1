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

void __cdecl bfmeLinearInsertFloatDescending(BfmeSortPair *last,
	BfmeSortPair pending);

// Retail's unguarded arm at 0x009F38FC pushes four words - the comparator byte,
// val.m_key, val.m_value and last - and cleans sixteen with `add esp, 0x10`,
// i.e. the three-argument __cdecl entry point.  The ledger's defining spelling
// at 0x009F2E30 takes only (last, pending) and reads the same eight bytes from
// [esp+4]..[esp+11]; the extra comparator word sits above them and is ignored.
// Spell the call through the wider entry point of that very symbol so the
// object references a name something defines.
typedef void (__cdecl *BfmeUnguardedLinearInsert)(BfmeSortPair *last,
	BfmeSortPair val, BfmeSortCompareDescending comp);

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
		((BfmeUnguardedLinearInsert)(void *)bfmeLinearInsertFloatDescending)(
			last, val, comp);
	}
}

template void __linear_insert<BfmeSortPair *, BfmeSortPair,
	BfmeSortCompareDescending>(BfmeSortPair *, BfmeSortPair *, BfmeSortPair,
	BfmeSortCompareDescending);

}
