// cl: /DNDEBUG /MD /EHsc
//
// The StringLookUp sort driver at 0x00438980 calls this STLport
// __introsort_loop instantiation for eight-byte records.

struct Q3SortElem8
{
	int m_a;
	float m_b;
};

struct Q3SortCompare
{
	void *m_state;
};

void j_00038b13(void);
void j_00002c93(void);
void j_00033672(void);

typedef Q3SortElem8 *(__cdecl *Q3Median)(Q3SortElem8 *, Q3SortElem8 *,
	Q3SortElem8 *, Q3SortCompare);
typedef Q3SortElem8 *(__cdecl *Q3Partition)(Q3SortElem8 *, Q3SortElem8 *,
	Q3SortElem8, Q3SortCompare);
typedef void (__cdecl *Q3PartialSort)(Q3SortElem8 *, Q3SortElem8 *,
	Q3SortElem8 *, int, Q3SortCompare);

// ?Gen004388C0@@YAXPAUQ3SortElem8@@00HUQ3SortCompare@@@Z
void Gen004388C0(Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *, int depth, Q3SortCompare comp)
{
	while (last - first > 16)
	{
		if (depth == 0)
		{
			((Q3PartialSort)j_00033672)(first, last, last,
				0, comp);
			return;
		}

		--depth;
		Q3SortElem8 *cut = ((Q3Partition)j_00002c93)(first, last,
			*(((Q3Median)j_00038b13)(first, first + (last - first) / 2,
				last - 1, comp)), comp);
		Gen004388C0(cut, last, (Q3SortElem8 *)0, depth, comp);
		last = cut;
	}
}
