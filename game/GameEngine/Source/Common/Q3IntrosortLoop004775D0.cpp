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
private:
	StringBase(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
public:
	void set(const StringBase<T> &other);
private:
	void *m_data;

	friend struct Q3SortElem16;
	friend class AsciiString;
};

// The real inline AsciiString forwarding layer is needed by the retail
// by-value copy schedule; its implicit destructor runs StringBase cleanup.
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
};

struct Q3SortElem16
{
	int m_a;
	int m_b;
	int m_c;
	AsciiString m_d;
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

__declspec(noinline) Q3SortElem16 *__unguarded_partition(Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16, Q3SortCompare);

void __partial_sort(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16 *, Q3SortCompare);
void __make_heap(Q3SortElem16 *, Q3SortElem16 *, Q3SortCompare,
	Q3SortElem16 *, int *);
struct Rva004748F0Element
{
    int m_a;
    int m_b;
    int m_c;
    AsciiString m_d;
};
struct Rva004748F0Compare { void *m_state; };
void Rva004748F0PopHeap(Rva004748F0Element *, Rva004748F0Element *, Rva004748F0Element *,
    Rva004748F0Element, Rva004748F0Compare, int *);
void bfmeSortVOV(void *, void *, void *);

// ?__partial_sort@@YAXPAUQ3SortElem16@@000UQ3SortCompare@@@Z
__declspec(noinline) void __partial_sort(Q3SortElem16 *first,
	Q3SortElem16 *middle, Q3SortElem16 *last, Q3SortElem16 *,
	Q3SortCompare incomingComp)
{
	Q3SortCompare comp = incomingComp;
	__make_heap(first, middle, comp, (Q3SortElem16 *)0, (int *)0);
	for (Q3SortElem16 *current = middle; current < last; ++current)
		if (comp(*current, *first))
			Rva004748F0PopHeap((Rva004748F0Element *)first, (Rva004748F0Element *)middle,
                (Rva004748F0Element *)current, *(Rva004748F0Element *)current,
                reinterpret_cast<const Rva004748F0Compare &>(comp), (int *)0);
	bfmeSortVOV(first, middle, comp.m_state);
}

__declspec(noinline) void iter_swap(Q3SortElem16 *, Q3SortElem16 *);

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

// ?__unguarded_partition@@YAPAUQ3SortElem16@@PAU1@0U1@UQ3SortCompare@@@Z
__declspec(noinline) Q3SortElem16 *__unguarded_partition(Q3SortElem16 *first,
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
		iter_swap(first, last);
		++first;
	}
}

// ?__introsort_loop@@YAXPAUQ3SortElem16@@00HUQ3SortCompare@@@Z
void __introsort_loop(Q3SortElem16 *first, Q3SortElem16 *last,
	Q3SortElem16 *, int depthLimit, const Q3SortCompare comp)
{
	while ((last - first) > 16)
	{
		if (depthLimit == 0)
		{
			__partial_sort(first, last, last, 0, comp);
			return;
		}

		--depthLimit;
		Q3SortElem16 *cut = __unguarded_partition(first, last,
			*Q3SortElem16Median(first, first + (last - first) / 2,
				last - 1, comp), comp);
		__introsort_loop(cut, last,
			(Q3SortElem16 *)0, depthLimit, comp);
		last = cut;
	}
}

// Retail 0x00473BC0/170: ordinary value swap with owning string copies.
__declspec(noinline) void iter_swap(Q3SortElem16 *first, Q3SortElem16 *last)
{
	Q3SortElem16 temporary = *first;
	*first = *last;
	*last = temporary;
}

// STLport __make_heap for the same owning 16-byte record.
// Retail 0x004749F0/116 ends at ret 0x00474A63; the partial-sort
// helper calls it through ILT 0x32646. Adjust_heap is the existing
// 283-byte body at 0x00474330, reached here through ILT 0x18ABB.
void bfmeAdjustHeap00474330(Rva004748F0Element *, int, int, Rva004748F0Element, Rva004748F0Compare);

void __make_heap(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortCompare comp, Q3SortElem16 *, int *)
{
    if (last - first < 2)
        return;
    int length = last - first;
    int parent = (length - 2) / 2;
    for (;;) {
        bfmeAdjustHeap00474330((Rva004748F0Element *)first, parent, length,
            *(Rva004748F0Element *)(first + parent), reinterpret_cast<const Rva004748F0Compare &>(comp));
        if (parent == 0)
            return;
        --parent;
    }
}

// STLport __push_heap; the matched adjust_heap body calls ILT0x49657
// to this full207B body at0x00473D60, ending ret0x00473E2E.
void __push_heap(Q3SortElem16 *first, int holeIndex,
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

__declspec(noinline) void __linear_insert(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16, Q3SortCompare);

// Retail92B ends at ret0x0047622B; matched final split0x00476880
// calls through ILT0x20D65. Linear insertion uses the same owning record.
void __insertion_sort(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortCompare comp)
{
    if (first == last)
        return;
    for (Q3SortElem16 *current = first + 1; current != last; ++current)
        __linear_insert(first, current, *current, comp);
}

// STLport random-access iterator tag inheritance (_iterator_base.h).
struct Q3InputIteratorTag {};
struct Q3ForwardIteratorTag : Q3InputIteratorTag {};
struct Q3BidirectionalIteratorTag : Q3ForwardIteratorTag {};
struct Q3IteratorCategory : Q3BidirectionalIteratorTag {};
inline Q3IteratorCategory Q3IteratorCategoryOf(Q3SortElem16 *const &)
{
    return Q3IteratorCategory();
}
struct BfmeElemVOX;
BfmeElemVOX *bfmeCopyBackVOX(const BfmeElemVOX *, const BfmeElemVOX *, BfmeElemVOX *);
// Retail passes two unused iterator tags through this cdecl call.
typedef Q3SortElem16 *(__cdecl *Q3CopyWithTags)(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *, const Q3IteratorCategory &, int *);
__declspec(noinline) void __unguarded_linear_insert(Q3SortElem16 *, Q3SortElem16, Q3SortCompare);

// Full retail191B ends at ret0x0047586E (exclusive0x0047586F).
void __linear_insert(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortElem16 value, Q3SortCompare comp)
{
    if (comp(value, *first)) {
        reinterpret_cast<Q3CopyWithTags>(bfmeCopyBackVOX)(first, last, last + 1,
            Q3IteratorCategoryOf(first), (int *)0);
        *first = value;
    } else {
        __unguarded_linear_insert(last, value, comp);
    }
}

// Full retail152B through ret0x00473D37, exclusive0x00473D38.
void __unguarded_linear_insert(Q3SortElem16 *last,
    Q3SortElem16 value, Q3SortCompare comp)
{
    Q3SortElem16 *next = last;
    --next;
    while (comp(value, *next)) {
        *last = *next;
        last = next;
        --next;
    }
    *last = value;
}
