// ?Rva00533650@@YAXPAUS4SortElem12_00533650@@0US4Cmp00533650@@@Z
// partial score=0.55 date=2026-09-06
// cl: /O2

// STLport sort driver over 12-byte records, retail 0x00533650, 91 bytes.
// Fuzzy twin of Rva002E1F10 (S4SortDriver002E1F10.cpp, ratio 0.895): same
// magic-multiply element-count divide and depth-limit loop, but the comp
// functor value is reloaded from the stack for each recursive call instead
// of being kept live in a callee-saved register across both calls.

struct S4SortElem12_00533650
{
	int m_a, m_b, m_c;
};

struct S4Cmp00533650
{
	void *m_state;
	bool operator()(S4SortElem12_00533650, S4SortElem12_00533650) const;
};

void Gen00533650IntrosortLoop(S4SortElem12_00533650 *first, S4SortElem12_00533650 *last,
	S4SortElem12_00533650 *, int depth, S4Cmp00533650 comp);
void Gen00533650FinalInsertionSort(S4SortElem12_00533650 *first, S4SortElem12_00533650 *last,
	S4Cmp00533650 comp);

void Rva00533650(S4SortElem12_00533650 *first, S4SortElem12_00533650 *last, S4Cmp00533650 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		Gen00533650IntrosortLoop(first, last, (S4SortElem12_00533650 *)0, k * 2, comp);
		Gen00533650FinalInsertionSort(first, last, comp);
	}
}
