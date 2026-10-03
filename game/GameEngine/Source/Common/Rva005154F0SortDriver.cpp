// cl: /O2
// stlport
// STLport sort driver, retail 0x005154F0, 75 bytes. Same outermost layer as
// Q3IntrosortFamilies.cpp's 74-byte drivers and ScoreRowSort.cpp's 75-byte
// driver: first != last, SGI __lg depth, introsort then final-insertion.
// There is no third comparator argument -- retail reloads `first` from its
// parameter home for both dummy slots (`[esp+0xC]` / `[esp+0x20]`), which is
// why this copy is one byte longer than the ebx-cached Q3 drivers. The first
// callee is the introsort loop at 0x005150A0; the second is the already-landed
// final-insertion pass Rva00513980 at 0x00513980. Element width is four
// (`sar eax,2`). Identity is not recovered; names are address-derived.

#include <functional>

struct Rva005154F0Elem
{
	int m_v;
};

struct Q3SortElem4
{
	void *m_item;
};

struct Q3SortCompare
{
	void *m_state;
};

void Rva00513980( Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare comp );

namespace _STL
{
template <class RandomAccessIter, class Tp, class Size, class Compare>
void __introsort_loop( RandomAccessIter, RandomAccessIter, Tp *, Size,
	Compare );
template <> void __introsort_loop<int *, int, int, less<int> >(
	int *, int *, int *, int, less<int> );
}

typedef void (__cdecl *Rva005154F0IntrosortCall)(Rva005154F0Elem *,
	Rva005154F0Elem *, Rva005154F0Elem *, int, void *);
typedef void (__cdecl *Rva005154F0FinalInsertionCall)(Rva005154F0Elem *,
	Rva005154F0Elem *, void *);
typedef void (__cdecl *Rva005154F0IntrosortTarget)(int *, int *, int *, int,
	_STL::less<int>);
typedef void (__cdecl *Rva005154F0FinalInsertionTarget)(Q3SortElem4 *,
	Q3SortElem4 *, Q3SortCompare);

void Rva005154F0( Rva005154F0Elem *first, Rva005154F0Elem *last )
{
	if ( first != last )
	{
		int n = last - first;
		int k;
		for ( k = 0; n != 1; n >>= 1 )
			++k;
		Rva005154F0IntrosortTarget introsortTarget =
			&_STL::__introsort_loop<int *, int, int, _STL::less<int> >;
		((Rva005154F0IntrosortCall)introsortTarget)(
			first, last, (Rva005154F0Elem *)0, k * 2,
			*(void * volatile *)&first );
		Rva005154F0FinalInsertionTarget finalInsertionTarget = &Rva00513980;
		((Rva005154F0FinalInsertionCall)finalInsertionTarget)(
			first, last, *(void * volatile *)&first );
	}
}
