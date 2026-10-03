// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Final insertion-sort pass used for BFME's eight-byte StringLookUp records.

struct Q3SortElem8
{
	int label;
	int info;
};

struct Q3SortCompare
{
	void *state;
};

struct BfmePairCXD;
struct GameTextStringLookUp;
struct GameTextStringCompare
{
	void *state;
};

void __cdecl GameTextInsertionSort00437E90(
	GameTextStringLookUp *first, GameTextStringLookUp *last,
	GameTextStringCompare comp);
void __cdecl bfmeGoCXD(BfmePairCXD *first, BfmePairCXD *last, void *extra);

typedef void (__cdecl *SortPass)(Q3SortElem8 *, Q3SortElem8 *, Q3SortCompare);

void Gen00438270(Q3SortElem8 *first, Q3SortElem8 *last, Q3SortCompare comp)
{
	if (last - first > 16)
	{
		((SortPass)GameTextInsertionSort00437E90)(first, first + 16, comp);
		((SortPass)bfmeGoCXD)(first + 16, last, comp);
	}
	else
	{
		((SortPass)GameTextInsertionSort00437E90)(first, last, comp);
	}
}
