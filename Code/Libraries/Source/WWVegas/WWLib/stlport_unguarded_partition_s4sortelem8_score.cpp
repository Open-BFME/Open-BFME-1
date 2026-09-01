// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<S4SortElem8 *, S4SortElem8,
// S4Cmp00575AA0>, retail 0x00575620, 119 bytes.  Both partition scans call
// the score comparator used by the adjacent exact insertion and heap helpers;
// the swaps copy the same proven two-dword element layout.

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

template <class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	S4SortElem8 temporary = *left;
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

template S4SortElem8 *__unguarded_partition<S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8,
	S4Cmp00575AA0);

}
