// cl: -GX-
// stlport
// Open-BFME7: STLport __push_heap<int*,int,int,Compare> at 0x0047DA30 (96 B),
// the S4StlSortHelpers.cpp S4_PUSH_HEAP family with a plain cdecl function
// pointer comparator (call dword ptr [esp+0x2c], add esp,8) instead of the
// in-place functor.
#include <algorithm>
typedef bool (__cdecl *S4CmpFn0047DA30)(int, int);
void s4ph0047DA30(int *first, int hole, int top, int value, S4CmpFn0047DA30 comp)
{
	_STL::__push_heap(first, hole, top, value, comp);
}
