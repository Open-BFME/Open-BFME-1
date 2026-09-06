// ??$__partial_sort@PAHHUQ4Sort00755050@@@_STL@@YAXPAH000UQ4Sort00755050@@@Z
// partial score=0.7 date=2026-09-06
// ??$__partial_sort@PAHHUQ4Sort00755050@@@_STL@@YAXPAH000UQ4Sort00755050@@@Z
// Open-BFME5: STLport __partial_sort over a four-byte scalar with
// Q4Sort00755050, retail 0x00754C60, 121 bytes.  Sibling of the
// Q4Sort0034BFC0/Q4Sort004566F0/Q4Sort004567A0 instantiations; own TU so
// Q4IntrosortLoop.cpp's matched rows stay put.
//
// cl: -GX-
// stlport

struct Q4Sort00755050
{
	void *m_state;
	bool operator()(int, int) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp);

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last, Tp *, Compare comp)
{
	__make_heap(first, middle, comp, (Tp *)0, (int *)0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			Tp item = *i;
			*i = *first;
			__adjust_heap(first, 0, (int)(middle - first), item, comp);
		}
	}
	sort_heap(first, middle, comp);
}

template void __partial_sort<int *, int, Q4Sort00755050>(
	int *, int *, int *, int *, Q4Sort00755050);

}
