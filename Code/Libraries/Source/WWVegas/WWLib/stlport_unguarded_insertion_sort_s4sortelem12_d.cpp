// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_insertion_sort_aux<S4SortElem12 *,
// S4SortElem12, S4Cmp00531FA0>, retail 0x0052FF20, 63 bytes.  The neighboring
// matched sort layers prove the specialization and the twelve-byte stride.

struct S4SortElem12
{
	int m_bfmeFirst;
	int m_bfmeKey;
	int m_bfmeThird;
};

struct S4Cmp00531FA0
{
	void *m_bfmeState;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, *i, comp);
}

template void __unguarded_insertion_sort_aux<S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *,
	S4Cmp00531FA0);

}
