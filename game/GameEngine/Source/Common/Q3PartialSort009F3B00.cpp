// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Near twin (diff 2 bytes) of Gen009F3B80 (0x009F3B80, Q3PartialSort009F3B80.cpp):
// same partial-sort-into-heap shape and callee set (__make_heap/__adjust_heap/
// sortHeap at 0x009F3400/0x009F3110/0x009F3930 instead of .../0x009F34B0/.../...),
// but the float compare uses a different comparison operator: retail's
// "test ah,0x41; jne" (le-skip for operator>) becomes "test ah,5; jp" here.

struct S4SortElem8_009F3400
{
	int m_a;
	int m_b;
};

// These cdecl declarations spell the existing matched STLport instantiations.
// The caller hands __adjust_heap a POD value as two adjacent dwords and the
// comparator as one dword: six stack slots, caller cleanup, no hidden slots.
// Keep that measured scalar view of the same physical by-value contract.
extern "C" void __cdecl __identifier("??$__make_heap@PAUS4SortElem8@@US4Cmp009F3400@@U1@H@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F3400@@0PAH@Z")(
    S4SortElem8_009F3400 *, S4SortElem8_009F3400 *, int,
    S4SortElem8_009F3400 *, int *);
extern "C" void __cdecl __identifier("??$__adjust_heap@PAUS4SortElem8@@HU1@US4Cmp009F3400@@@_STL@@YAXPAUS4SortElem8@@HHU1@US4Cmp009F3400@@@Z")(
    S4SortElem8_009F3400 *, int, int, int, int, int);
extern "C" void __cdecl __identifier("??$sort_heap@PAUS4SortElem8@@US4Cmp009F3400@@@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F3400@@@Z")(
    S4SortElem8_009F3400 *, S4SortElem8_009F3400 *, int);

void Gen009F3B00(S4SortElem8_009F3400 *first, S4SortElem8_009F3400 *middle,
	S4SortElem8_009F3400 *last, int, int comp)
{
	__identifier("??$__make_heap@PAUS4SortElem8@@US4Cmp009F3400@@U1@H@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F3400@@0PAH@Z")(first, middle, comp, (S4SortElem8_009F3400 *)0, (int *)0);
	for (S4SortElem8_009F3400 *i = middle; i < last; ++i) {
	if (*(const float *)&i->m_b < *(const float *)&first->m_b) {
            int itemA = i->m_a;
            int itemB = i->m_b;
			int frontA = first->m_a;
			__identifier("??$__adjust_heap@PAUS4SortElem8@@HU1@US4Cmp009F3400@@@_STL@@YAXPAUS4SortElem8@@HHU1@US4Cmp009F3400@@@Z")(
				(i->m_b = first->m_b, first),
				(i->m_a = frontA, 0),
				(int)(middle - first), itemA, itemB, comp);
		}
	}
	__identifier("??$sort_heap@PAUS4SortElem8@@US4Cmp009F3400@@@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F3400@@@Z")(first, middle, comp);
}
