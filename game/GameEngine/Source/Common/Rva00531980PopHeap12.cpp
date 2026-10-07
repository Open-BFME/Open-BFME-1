// ?Rva00531980PopHeap@@YAXPAUS4SortElem12Pod@@00U1@PAXPAH@Z
// cl: /DNDEBUG /MD /EHsc

struct S4SortElem12Pod
{
	int m_a;
	int m_b;
	int m_c;
};

// The matched adjust_heap at 0x005300E0 spells the same twelve-byte record S4SortElem12.
struct S4SortElem12
{
	int m_a;
	int m_b;
	int m_c;
};

void __adjust_heap(S4SortElem12 *first, int hole, int len,
	S4SortElem12 value, void *comp);

void Rva00531980PopHeap(S4SortElem12Pod *first, S4SortElem12Pod *last,
	S4SortElem12Pod *result, S4SortElem12Pod value, void *comp, int *)
{
	*result = *first;
	__adjust_heap(reinterpret_cast<S4SortElem12 *>(first), 0, last - first,
		*reinterpret_cast<S4SortElem12 *>(&value), comp);
}
