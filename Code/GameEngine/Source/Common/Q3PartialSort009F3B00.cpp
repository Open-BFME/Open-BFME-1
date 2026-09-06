// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Near twin (diff 2 bytes) of Gen009F3B80 (0x009F3B80, Q3PartialSort009F3B80.cpp):
// same partial-sort-into-heap shape and callee set (__make_heap/__adjust_heap/
// sortHeap at 0x009F3400/0x009F3110/0x009F3930 instead of .../0x009F34B0/.../...),
// but the float compare uses a different comparison operator: retail's
// "test ah,0x41; jne" (le-skip for operator>) becomes "test ah,5; jp" here.

struct S4SortElem8_009F3400
{
	int m_a;
	int m_b;
};

void q3MakeHeap009F3400(S4SortElem8_009F3400 *, S4SortElem8_009F3400 *, int,
	S4SortElem8_009F3400 *, int *);
void q3AdjustHeap009F3400(S4SortElem8_009F3400 *, int, int, int, int, int);
void q3SortHeap009F3400(S4SortElem8_009F3400 *, S4SortElem8_009F3400 *, int);

void Gen009F3B00(S4SortElem8_009F3400 *first, S4SortElem8_009F3400 *middle,
	S4SortElem8_009F3400 *last, int, int comp)
{
	q3MakeHeap009F3400(first, middle, comp, (S4SortElem8_009F3400 *)0, (int *)0);
	for (S4SortElem8_009F3400 *i = middle; i < last; ++i) {
	if (*(const float *)&i->m_b < *(const float *)&first->m_b) {
            int itemA = i->m_a;
            int itemB = i->m_b;
			int frontA = first->m_a;
			q3AdjustHeap009F3400(
				(i->m_b = first->m_b, first),
				(i->m_a = frontA, 0),
				(int)(middle - first), itemA, itemB, comp);
		}
	}
	q3SortHeap009F3400(first, middle, comp);
}
