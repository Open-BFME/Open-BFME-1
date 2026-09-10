// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the 16-byte STLport __introsort_loop called by the matched
// Rva00477960 driver.  The retail body inlines median-of-three over the first
// integer, copies the trailing StringBase<char> handle, then calls the partition,
// recursive loop and typed partial-sort helper below.
// Parent raw tracing: ILT1492A -> iter-swap473BC0/170B (two pointers),
// ILT34F95 -> partition4747F0/133B, ILTAEBB -> this217B loop,
// ILT32501 -> partial-sort4768F0/130B. Its fourth argument is the
// STLport value-type pointer, not a depth integer (_algo.c __partial_sort).
// noinline keeps the separate retail partition call; copies/releases use
// actual StringBase<char> constructors and releaseBuffer, not dummy owners.

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	void set(const StringBase<T> &other);
	void *m_data;

	friend struct Q3SortElem16;
};

struct Q3SortElem16
{
	int m_a;
	int m_b;
	int m_c;
	StringBase<char> m_d;
};

typedef char Q3ElementIs16[(sizeof(Q3SortElem16) == 16) ? 1 : -1];

struct Q3SortCompare
{
	void *m_state;

	__forceinline bool operator()(const Q3SortElem16 &left,
		const Q3SortElem16 &right) const
	{
		return left.m_a < right.m_a;
	}
};

__declspec(noinline) Q3SortElem16 *Q3Partition004775D0(Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16, Q3SortCompare);

void Q3PartialSort004775D0(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16 *, Q3SortCompare);

__declspec(noinline) void Q3IterSwap00473BC0(Q3SortElem16 *, Q3SortElem16 *);

static __forceinline const Q3SortElem16 *Q3SortElem16Median(
	const Q3SortElem16 *a, const Q3SortElem16 *b,
	const Q3SortElem16 *c, const Q3SortCompare &comp)
{
	if (comp(*a, *b))
	{
		if (comp(*b, *c))
			return b;
		if (comp(*a, *c))
			return c;
		return a;
	}
	if (comp(*a, *c))
		return a;
	if (comp(*b, *c))
		return c;
	return b;
}

// ?Q3Partition004775D0@@YAPAUQ3SortElem16@@PAU1@0U1@UQ3SortCompare@@@Z
__declspec(noinline) Q3SortElem16 *Q3Partition004775D0(Q3SortElem16 *first,
	Q3SortElem16 *last, Q3SortElem16 value, Q3SortCompare comp)
{
	for (;;)
	{
		while (comp(*first, value))
			++first;
		--last;
		while (comp(value, *last))
			--last;
		if (!(first < last))
			return first;
		Q3IterSwap00473BC0(first, last);
		++first;
	}
}

// ?Gen004775D0@@YAXPAUQ3SortElem16@@00HUQ3SortCompare@@@Z
void Gen004775D0(Q3SortElem16 *first, Q3SortElem16 *last,
	Q3SortElem16 *, int depthLimit, const Q3SortCompare comp)
{
	while ((last - first) > 16)
	{
		if (depthLimit == 0)
		{
			Q3PartialSort004775D0(first, last, last, 0, comp);
			return;
		}

		--depthLimit;
		Q3SortElem16 *cut = Q3Partition004775D0(first, last,
			*Q3SortElem16Median(first, first + (last - first) / 2,
				last - 1, comp), comp);
		Gen004775D0(cut, last,
			(Q3SortElem16 *)0, depthLimit, comp);
		last = cut;
	}
}

// Retail 0x00473BC0/170: ordinary value swap with owning string copies.
__declspec(noinline) void Q3IterSwap00473BC0(Q3SortElem16 *first, Q3SortElem16 *last)
{
	Q3SortElem16 temporary = *first;
	*first = *last;
	*last = temporary;
}

// STLport __make_heap for the same owning 16-byte record.
// Retail 0x004749F0/116 ends at ret 0x00474A63; the partial-sort
// helper calls it through ILT 0x32646. Adjust_heap is the existing
// 283-byte body at 0x00474330, reached here through ILT 0x18ABB.
void Q3AdjustHeap00474330(Q3SortElem16 *, int, int, Q3SortElem16, Q3SortCompare);

void Q3MakeHeap004749F0(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortCompare comp, Q3SortElem16 *, int *)
{
    if (last - first < 2)
        return;
    int length = last - first;
    int parent = (length - 2) / 2;
    for (;;) {
        Q3AdjustHeap00474330(first, parent, length, *(first + parent), comp);
        if (parent == 0)
            return;
        --parent;
    }
}

// STLport __push_heap; the matched adjust_heap body calls ILT0x49657
// to this full207B body at0x00473D60, ending ret0x00473E2E.
void Q3PushHeap00473D60(Q3SortElem16 *first, int holeIndex,
    int topIndex, Q3SortElem16 value, Q3SortCompare comp)
{
    int parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && comp(first[parent], value)) {
        first[holeIndex] = first[parent];
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    first[holeIndex] = value;
}
