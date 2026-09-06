// ?s4ph0047da30@@YAXPAHHHHP6A_NHH@Z@Z
// partial score=0.3 date=2026-09-05
// cl: -GX-
// stlport
//
// FUZZY-TWIN of Code/GameEngine/Source/Common/S4StlSortHelpers.cpp's
// S4_PUSH_HEAP(003408C0) family (see that file's header comment for the full
// derivation of the __push_heap<int> shape). The only byte difference here:
// the comparator is invoked with `call dword ptr [esp+0x2C]` -- a plain
// cdecl function pointer -- rather than the `lea ecx,[esp+0x2C]`
// thiscall-on-functor-in-place call the S4Cmp family uses. Same five
// arguments, same divide-by-two hole/parent shape, same __cdecl callee
// (add esp,8 caller cleanup) matching a bool(__cdecl*)(int,int).

typedef bool (__cdecl *S4CmpFnPtr0047DA30)(int, int);

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), val))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<int *, int, int, S4CmpFnPtr0047DA30>(
	int *, int, int, int, S4CmpFnPtr0047DA30);

}

void s4ph0047da30(int *first, int hole, int top, int value,
	S4CmpFnPtr0047DA30 comp)
{
	_STL::__push_heap(first, hole, top, value, comp);
}
