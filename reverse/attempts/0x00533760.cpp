// ?Rva_00533760@@YAXPAUS4SortElem12_00533760@@0US4Cmp_00533760@@@Z
// partial score=0.55 date=2026-09-06
// cl: /O2

// STLport sort driver over 12-byte records, retail 0x00533760, 91 bytes.
// Fuzzy twin of Rva002E1F10 (S4SortDriver002E1F10.cpp, ratio 0.895): same
// magic-multiply element-count divide and depth-limit loop, but the comp
// functor value is reloaded from the stack for each recursive call instead
// of being kept live in a callee-saved register across both calls (same
// unresolved register-allocation delta as 0x00533650, see reverse/attempts/0x00533650.cpp).

struct S4SortElem12_00533760
{
	int m_a, m_b, m_c;
};

struct S4Cmp_00533760
{
	void *m_state;
	bool operator()(S4SortElem12_00533760, S4SortElem12_00533760) const;
};

void Gen_00533760_IntrosortLoop(S4SortElem12_00533760 *first, S4SortElem12_00533760 *last,
	S4SortElem12_00533760 *, int depth, S4Cmp_00533760 comp);
void Gen_00533760_FinalInsertionSort(S4SortElem12_00533760 *first, S4SortElem12_00533760 *last,
	S4Cmp_00533760 comp);

void Rva_00533760(S4SortElem12_00533760 *first, S4SortElem12_00533760 *last, S4Cmp_00533760 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		Gen_00533760_IntrosortLoop(first, last, (S4SortElem12_00533760 *)0, k * 2, comp);
		Gen_00533760_FinalInsertionSort(first, last, comp);
	}
}
