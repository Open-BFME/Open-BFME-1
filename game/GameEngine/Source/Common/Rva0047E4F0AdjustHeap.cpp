// cl: -GX-
// stlport
// Open-BFME7: the 111-byte STLport __adjust_heap<int*, int, int, Compare>
// body at 0x0047E4F0.  Rva00483E00PartialSortInt.cpp is a matched real caller
// and passes five cdecl dwords: int*, hole index, length, int value, and a
// bool (__cdecl *)(int, int) comparator.  The retail body ends in the matched
// function-pointer __push_heap<int*, int, int, Compare> family at 0x0047DA30.
#include <algorithm>

typedef bool (__cdecl *Rva0047E4F0Compare)( int, int );

void rva0047E4F0( int *first, int holeIndex, int len, int value,
	Rva0047E4F0Compare comp )
{
	_STL::__adjust_heap( first, holeIndex, len, value, comp );
}
