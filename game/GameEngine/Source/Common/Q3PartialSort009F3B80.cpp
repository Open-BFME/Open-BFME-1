// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Q3SortElem8
{
	int m_a;
	int m_b;
};

// Retail STLport instantiations at 0x009F34B0, 0x009F3190 and 0x009F3990.
// Their cdecl ABI passes the two element words and comparator word by value.
// Use their exact symbols while retaining this TU's flattened argument view.
extern "C" void __cdecl __identifier("??$__make_heap@PAUS4SortElem8@@US4Cmp009F34B0@@U1@H@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F34B0@@0PAH@Z")(Q3SortElem8 *, Q3SortElem8 *, int,
	Q3SortElem8 *, int *);
extern "C" void __cdecl __identifier("??$__adjust_heap@PAUS4SortElem8@@HU1@US4Cmp009F34B0@@@_STL@@YAXPAUS4SortElem8@@HHU1@US4Cmp009F34B0@@@Z")(Q3SortElem8 *, int, int, int, int, int);
extern "C" void __cdecl __identifier("??$sort_heap@PAUS4SortElem8@@US4Cmp009F34B0@@@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F34B0@@@Z")(Q3SortElem8 *, Q3SortElem8 *, int);

void Gen009F3B80(Q3SortElem8 *first, Q3SortElem8 *middle,
	Q3SortElem8 *last, int, int comp)
{
	__identifier("??$__make_heap@PAUS4SortElem8@@US4Cmp009F34B0@@U1@H@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F34B0@@0PAH@Z")(first, middle, comp, (Q3SortElem8 *)0, (int *)0);
	for (Q3SortElem8 *i = middle; i < last; ++i) {
	if (*(const float *)&i->m_b > *(const float *)&first->m_b) {
            int itemA = i->m_a;
            int itemB = i->m_b;
			int frontA = first->m_a;
			__identifier("??$__adjust_heap@PAUS4SortElem8@@HU1@US4Cmp009F34B0@@@_STL@@YAXPAUS4SortElem8@@HHU1@US4Cmp009F34B0@@@Z")(
				(i->m_b = first->m_b, first),
				(i->m_a = frontA, 0),
				(int)(middle - first), itemA, itemB, comp);
		}
	}
	__identifier("??$sort_heap@PAUS4SortElem8@@US4Cmp009F34B0@@@_STL@@YAXPAUS4SortElem8@@0US4Cmp009F34B0@@@Z")(first, middle, comp);
}
