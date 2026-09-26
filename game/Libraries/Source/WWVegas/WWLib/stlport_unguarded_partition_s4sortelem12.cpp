// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<S4SortElem12 *, S4SortElem12,
// S4Cmp00572410>, retail 0x00572410, 120 bytes.  Leaf partition: inlined
// first-field less, 12-byte stride, three-dword swap.  S4SortElem12 is a
// width stand-in; the element type beyond key-in-first-int is not recovered.

struct S4SortElem12
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00572410
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

template <class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	S4SortElem12 temporary = *left;
	*left = *right;
	*right = temporary;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template S4SortElem12 *__unguarded_partition<S4SortElem12 *, S4SortElem12,
	S4Cmp00572410>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp00572410);

}
