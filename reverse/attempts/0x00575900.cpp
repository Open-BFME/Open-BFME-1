// ?Rva_00575900@@YAXPAUS4SortElem12_00575900@@0US4Cmp_00575900@@@Z
// partial score=0.55 date=2026-09-06
// cl: /O2

// STLport sort driver over 12-byte records, retail 0x00575900, 91 bytes.
// Fuzzy twin of Rva002E1F10 (S4SortDriver002E1F10.cpp, ratio 0.895): same
// magic-multiply element-count divide and depth-limit loop, but the comp
// functor value is reloaded from the stack for each recursive call instead
// of being kept live in a callee-saved register across both calls (same
// unresolved register-allocation delta as 0x00533650, see reverse/attempts/0x00533650.cpp).

struct S4SortElem12_00575900
{
	int m_a, m_b, m_c;
};

struct S4Cmp_00575900
{
	void *m_state;
	bool operator()(S4SortElem12_00575900, S4SortElem12_00575900) const;
};

void Gen_00575900_IntrosortLoop(S4SortElem12_00575900 *first, S4SortElem12_00575900 *last,
	S4SortElem12_00575900 *, int depth, S4Cmp_00575900 comp);
void Gen_00575900_FinalInsertionSort(S4SortElem12_00575900 *first, S4SortElem12_00575900 *last,
	S4Cmp_00575900 comp);

void Rva_00575900(S4SortElem12_00575900 *first, S4SortElem12_00575900 *last, S4Cmp_00575900 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		Gen_00575900_IntrosortLoop(first, last, (S4SortElem12_00575900 *)0, k * 2, comp);
		Gen_00575900_FinalInsertionSort(first, last, comp);
	}
}
