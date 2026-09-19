// cl: /DNDEBUG /MD /EHsc
// stlport
// _STL::__insertion_sort<BfmeSortPair *, BfmeSortCompareDescending>, retail
// 0x009F3AC0. Same shape as Rva009F3A80InsertionSort.cpp (ascending) but
// calls the real __linear_insert<BfmeSortPair*, BfmeSortPair,
// BfmeSortCompareDescending> instantiation already used by
// stlport_linear_insert_bfmesortpair_descending.cpp.
struct BfmeSortPair
{
	unsigned int m_value;
	float m_key;
};

struct BfmeSortCompareDescending
{
	bool operator()(const BfmeSortPair& left, const BfmeSortPair& right) const
	{
		return left.m_key > right.m_key;
	}
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (first == last)
		return;

	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<BfmeSortPair*, BfmeSortCompareDescending>(
	BfmeSortPair*, BfmeSortPair*, BfmeSortCompareDescending);

}
