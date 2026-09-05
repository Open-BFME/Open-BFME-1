// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport sort_heap over a trivially-copyable twelve-byte
// element, retail 0x005327C0, 158 bytes. Same family as
// Code/GameEngine/Source/Common/S4MakeHeapElem12Pod.cpp (__make_heap,
// 0x00531B20) and Code/GameEngine/Source/Common/S4SortHeapElem12.cpp
// (sort_heap, 0x00573A30) -- but the pointers here are untyped (every
// index is computed by the same 0x2AAAAAAB / 12 magic-number division
// S4MakeHeapElem12Pod.cpp's __make_heap uses, not the compiler's automatic
// pointer-stride subtraction S4SortHeapElem12.cpp's typed version gets),
// so the element type is not statically known at these call sites and the
// same address-derived S4SortElem12Pod stand-in applies. The out-of-line
// adjust-heap callee is the same bfmeAdjustHeap00531B20
// (retail 0x0001D0B6, already pinned in reverse/symbols.csv).
//
// Identity beyond width/shape is not recovered; the owner and comparator
// are address-derived like their S4* neighbours.

struct S4SortElem12Pod
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void bfmeAdjustHeap00531B20(S4SortElem12Pod *first, int holeIndex, int len,
	S4SortElem12Pod value, void *comp);

void gen005327C0(void *firstVoid, void *lastVoid, void *comp)
{
	char *first = (char *)firstVoid;
	char *last = (char *)lastVoid;

	while ((last - first) / 12 > 1)
	{
		S4SortElem12Pod val = *(S4SortElem12Pod *)(last - 12);
		*(S4SortElem12Pod *)(last - 12) = *(S4SortElem12Pod *)first;
		bfmeAdjustHeap00531B20((S4SortElem12Pod *)first, 0,
			(int)((last - 12 - first) / 12), val, comp);
		last -= 12;
	}
}
