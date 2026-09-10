// ?Rva00531980PopHeap@@YAXPAUS4SortElem12Pod@@00U1@PAXPAH@Z
// cl: /DNDEBUG /MD /EHsc

struct S4SortElem12Pod
{
	int m_a;
	int m_b;
	int m_c;
};

void bfmeAdjustHeap00531B20(S4SortElem12Pod *first, int hole, int len,
	S4SortElem12Pod value, void *comp);

void Rva00531980PopHeap(S4SortElem12Pod *first, S4SortElem12Pod *last,
	S4SortElem12Pod *result, S4SortElem12Pod value, void *comp, int *)
{
	*result = *first;
	bfmeAdjustHeap00531B20(first, 0, last - first, value, comp);
}
