// cl: /O2

// STLport sort driver over 12-byte records, retail 0x002E1F10, 90 bytes.
// Same shape as Q3IntrosortFamilies.cpp's 74-byte drivers, but the element
// stride is 12 so last-first is the 0x2AAAAAAB magic multiply.

struct S4SortElem12
{
	int m_a, m_b, m_c;
};

struct S4Cmp002E1690
{
	void *m_state;
	bool operator()(S4SortElem12, S4SortElem12) const;
};

void Gen002E1B60(S4SortElem12 *first, S4SortElem12 *last, S4SortElem12 *,
	int depth, S4Cmp002E1690 comp);
void Gen002E1690(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E1690 comp);

void Rva002E1F10(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E1690 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		Gen002E1B60(first, last, (S4SortElem12 *)0, k * 2, comp);
		Gen002E1690(first, last, comp);
	}
}
