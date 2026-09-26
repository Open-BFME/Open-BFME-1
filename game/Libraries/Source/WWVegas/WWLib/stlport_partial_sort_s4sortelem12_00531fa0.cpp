// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport __partial_sort over the twelve-byte S4 record ordered by
// S4SortElem12::BfmeLess0052E880, retail 0x00532CC0, 233 bytes.  The
// introsort caller at 0x005331E0 and the surrounding insertion-sort family
// use this same pointer, key, and third-word record layout.

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

struct S4Cmp00531FA0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
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
};

void gen00531B20(void *first, void *last, void *comp, int, int);
void bfmeAdjustHeap005300E0(S4SortElem12 *first, int holeIndex, int len,
	S4SortElem12 value, void *comp);
void gen005327C0(void *first, void *last, void *comp);

namespace _STL
{

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last, Tp *, Compare comp)
{
	gen00531B20(first, middle, comp.m_bfmeState, 0, 0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			Tp item = *i;
			*i = *first;
			bfmeAdjustHeap005300E0(first, 0,
				(int)(middle - first), item, comp.m_bfmeState);
		}
	}
	gen005327C0(first, middle, comp.m_bfmeState);
}

template void __partial_sort<S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *,
	S4SortElem12 *, S4Cmp00531FA0);

}
