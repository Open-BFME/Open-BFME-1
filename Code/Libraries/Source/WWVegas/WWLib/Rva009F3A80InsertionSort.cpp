// cl: /DNDEBUG /MD /EHsc
// stlport
// _STL::__insertion_sort<BfmeSortPair *, BfmeSortCompare>, retail
// 0x009F3A80. Same shape as
// Code/Libraries/Source/WWVegas/WWLib/stlport_insertion_sort_s4sortelem12.cpp
// but calling the real __linear_insert<BfmeSortPair*, BfmeSortPair,
// BfmeSortCompare> instantiation already used by
// stlport_linear_insert_bfmesortpair_ascending.cpp.
struct BfmeSortPair
{
	unsigned int m_value;
	float m_key;
};

struct BfmeSortCompare
{
	bool operator()(const BfmeSortPair& left, const BfmeSortPair& right) const
	{
		return left.m_key < right.m_key;
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

template void __insertion_sort<BfmeSortPair*, BfmeSortCompare>(
	BfmeSortPair*, BfmeSortPair*, BfmeSortCompare);

}
