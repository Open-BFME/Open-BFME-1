// ?q3PartialSort009F3D80@@YAXPAUQ3SortElem8@@00UQ3SortCompare@@@Z
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME7: the two STLport partial_sort entry wrappers at 0x009F3D80 and
// 0x009F3DA0 (31 B each): pass the (T*)0 value-type tag into the depth-zero
// bodies Gen009F3B00 / Gen009F3B80.
struct Q3SortElem8 { int m_a; int m_b; };
struct Q3SortCompare { int m_v; };
void Gen009F3B00(Q3SortElem8 *first, Q3SortElem8 *middle, Q3SortElem8 *last, int, Q3SortCompare comp);
void Gen009F3B80(Q3SortElem8 *first, Q3SortElem8 *middle, Q3SortElem8 *last, int, Q3SortCompare comp);
void q3PartialSort009F3D80(Q3SortElem8 *first, Q3SortElem8 *middle, Q3SortElem8 *last, Q3SortCompare comp)
{
	Gen009F3B00(first, middle, last, 0, comp);
}
// ?q3PartialSort009F3DA0@@YAXPAUQ3SortElem8@@00UQ3SortCompare@@@Z
void q3PartialSort009F3DA0(Q3SortElem8 *first, Q3SortElem8 *middle, Q3SortElem8 *last, Q3SortCompare comp)
{
	Gen009F3B80(first, middle, last, 0, comp);
}
