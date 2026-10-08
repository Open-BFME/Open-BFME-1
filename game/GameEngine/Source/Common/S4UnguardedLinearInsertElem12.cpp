// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: _STL::__unguarded_linear_insert<S4SortElem12 *, S4SortElem12,
// S4Cmp00531FA0>, retail 0x0052F110, 109 bytes: the matched __linear_insert
// 0x0052FE90 and __unguarded_insertion_sort_aux 0x0052FF20 of the
// S4Cmp00531FA0 sort reach it through ILT 0x0001649B, where symbols.csv pins
// that spelling.  The comparison is the same BfmeLess0052E880 the
// matched linear_insert at 0x0052FE90 already names: key descending, then
// the pointed-to StringBase at +4.

#include "string_base.h"

struct S4Named0052E880
{
	int m_bfmeUnused;
	StringBase<char> m_bfmeName;
};

struct S4SortElem12
{
	S4Named0052E880 *m_bfmeObj;
	int m_bfmeKey;
	int m_bfmeThird;
};

static bool bfmeLessVal(const S4SortElem12 &left, const S4SortElem12 &right)
{
	if (left.m_bfmeKey == right.m_bfmeKey)
	{
		if (left.m_bfmeObj != 0)
		{
			if (right.m_bfmeObj == 0)
				goto retFalse;
			return left.m_bfmeObj->m_bfmeName.compareNoCase(
				right.m_bfmeObj->m_bfmeName) < 0;
		}
		if (right.m_bfmeObj == 0)
		{
retFalse:
			return false;
		}
		return true;
	}
	return left.m_bfmeKey > right.m_bfmeKey;
}

struct S4Cmp00531FA0
{
	void *m_bfmeState;

	// A member template keeps this TU's inline comparator out of any shared
	// ??RS4Cmp00531FA0 COMDAT.
	template <class Elem>
	bool operator()(const Elem &left, const Elem &right) const
	{
		return bfmeLessVal(left, right);
	}
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
	RandomAccessIter next = last;
	--next;
	while (comp(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

template void __unguarded_linear_insert<S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0>(S4SortElem12 *, S4SortElem12, S4Cmp00531FA0);

}
