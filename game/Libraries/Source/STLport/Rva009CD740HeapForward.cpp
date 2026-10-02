// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// RVA009CD740 is INT3-delimited28B through plain RET at+0x1b.
// It forwards three incoming cdecl slots and two zero type/distance tags.
// Existing Q3PartialSort009CD980.cpp uses the same five-slot binding;
// retail009CD998 calls009CD5E0 with20B caller cleanup. The independently
// decoded80B helper uses first/last/compare and ignores the two zero tags.
// Q3 names are existing TU ABI views; this wrapper's original identity is
// unproven, so its function name keeps the retail address.
#include "ascii_string.h"
struct Q3SortElem4 { AsciiString m_base; };
struct Q3SortCompare {};
void q3MakeHeap(Q3SortElem4 *,Q3SortElem4 *,Q3SortCompare,Q3SortElem4 *,int *);
void rva009CD740(Q3SortElem4 *first,Q3SortElem4 *last,Q3SortCompare compare)
{
    q3MakeHeap(first,last,compare,(Q3SortElem4 *)0,(int *)0);
}
