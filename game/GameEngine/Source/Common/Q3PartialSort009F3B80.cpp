// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Q3SortElem8
{
	int m_a;
	int m_b;
};

void q3MakeHeap(Q3SortElem8 *, Q3SortElem8 *, int,
	Q3SortElem8 *, int *);
void q3AdjustHeap(Q3SortElem8 *, int, int, int, int, int);
void q3SortHeap(Q3SortElem8 *, Q3SortElem8 *, int);

void Gen009F3B80(Q3SortElem8 *first, Q3SortElem8 *middle,
	Q3SortElem8 *last, int, int comp)
{
	q3MakeHeap(first, middle, comp, (Q3SortElem8 *)0, (int *)0);
	for (Q3SortElem8 *i = middle; i < last; ++i) {
	if (*(const float *)&i->m_b > *(const float *)&first->m_b) {
            int itemA = i->m_a;
            int itemB = i->m_b;
			int frontA = first->m_a;
			q3AdjustHeap(
				(i->m_b = first->m_b, first),
				(i->m_a = frontA, 0),
				(int)(middle - first), itemA, itemB, comp);
		}
	}
	q3SortHeap(first, middle, comp);
}
