// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__linear_insert<S4SortElem12 *, S4SortElem12,
// S4Cmp00531FA0>, retail 0x0052FE90, 114 bytes.  The matched insertion-sort
// caller at 0x00531720 proves the specialization.  The comparator and both
// algorithm helpers are decoded from this body's direct ILT calls.

struct S4SortElem12
{
	int m_bfmeFirst;
	int m_bfmeKey;
	int m_bfmeThird;

	bool BfmeLess0052E880(const S4SortElem12 &other) const;
};

struct S4Cmp00531FA0
{
	void *m_bfmeState;

	// Defined by the introsort and partial-sort TUs (retail's out-of-line
	// comparator); this TU compares through S4ForwardLess so it emits no
	// differing thin copy of it.
	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const;
};

struct S4ForwardLess
{
	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.BfmeLess0052E880(right);
	}
};

namespace _STL
{

struct random_access_iterator_tag
{
};

// ILT00019CBD -> 0052D370/86: cdecl five pointers, EAX result, bare RET.
extern "C" S4SortElem12 *__cdecl __identifier("??$__copy_backward@PAUWeaponRecoilInfo@W3DModelDraw@@PAU12@H@_STL@@YAPAUWeaponRecoilInfo@W3DModelDraw@@PAU12@00ABUrandom_access_iterator_tag@0@PAH@Z")(S4SortElem12 *first,
	S4SortElem12 *last, S4SortElem12 *result,
	const random_access_iterator_tag &tag, int *distance);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first,
	RandomAccessIter last, Tp val, Compare comp)
{
	S4ForwardLess less;
	if (less(val, *first))
	{
		random_access_iterator_tag tag;
		__identifier("??$__copy_backward@PAUWeaponRecoilInfo@W3DModelDraw@@PAU12@H@_STL@@YAPAUWeaponRecoilInfo@W3DModelDraw@@PAU12@00ABUrandom_access_iterator_tag@0@PAH@Z")(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0);

}
