// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Twin of 0x00438270 (GameTextFinalInsertionSort.cpp): same threshold-split
// final insertion sort shape over Q3SortElem8, with different sort-pass
// callees (0x002618D0 / 0x002610B0).

struct Q3SortElem8
{
	int label;
	int info;
};

struct Q3SortCompare
{
	void *state;
};


// Both sort passes are matched ledger rows (callees.py): the body at
// 0x002618D0 is rva002618D0ForEach and the one at 0x002610B0 is bfmeGoCXB.
// Each takes the comparator's single word where this caller passes it by value.
struct Rva002618D0Elem;
struct BfmePairCXB;
void rva002618D0ForEach(Rva002618D0Elem *, Rva002618D0Elem *, void *);
void bfmeGoCXB(BfmePairCXB *, BfmePairCXB *, void *);


typedef void (__cdecl *SortPass)(Q3SortElem8 *, Q3SortElem8 *, Q3SortCompare);

void Gen00261A20(Q3SortElem8 *first, Q3SortElem8 *last, Q3SortCompare comp)
{
	if (last - first > 16)
	{
		((SortPass)rva002618D0ForEach)(first, first + 16, comp);
		((SortPass)bfmeGoCXB)(first + 16, last, comp);
	}
	else
	{
		((SortPass)rva002618D0ForEach)(first, last, comp);
	}
}
