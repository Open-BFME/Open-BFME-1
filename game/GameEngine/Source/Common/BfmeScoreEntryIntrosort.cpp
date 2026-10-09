// cl: /DNDEBUG /MD /EHsc

struct BfmeScoreEntry
{
	int m_words[4];
};

struct BfmeScoreEntryLess
{
	void *m_state;
	bool operator()(const BfmeScoreEntry *left,
		const BfmeScoreEntry *right) const;
};

// Callees per tools/callees.py: ILT 0x2A595 -> 0x005724D0 and ILT 0x37B5F ->
// 0x00574410, the matched STLport helpers of BfmeScoreEntryUnguardedPartition.cpp
// and BfmeScoreEntrySort.cpp; ILT 0x152C1 -> 0x00575450 is this body itself.
namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last, Tp *, Compare comp);

}

void Gen00575450(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntry *tag, int depthLimit, BfmeScoreEntryLess comp);

static __forceinline BfmeScoreEntry *BfmeScoreEntryMedian00575450(
	const BfmeScoreEntry *a, const BfmeScoreEntry *b,
	const BfmeScoreEntry *c, const BfmeScoreEntryLess &comp)
{
	if (comp(a, b))
	{
		if (comp(b, c))
			return (BfmeScoreEntry *)b;
		if (comp(a, c))
			return (BfmeScoreEntry *)c;
		return (BfmeScoreEntry *)a;
	}
	if (comp(a, c))
		return (BfmeScoreEntry *)a;
	if (comp(b, c))
		return (BfmeScoreEntry *)c;
	return (BfmeScoreEntry *)b;
}

void Gen00575450(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntry *tag, int depthLimit, BfmeScoreEntryLess comp)
{
	while (last - first > 16)
	{
		if (depthLimit == 0)
		{
			_STL::__partial_sort<BfmeScoreEntry *, int, BfmeScoreEntry,
				BfmeScoreEntryLess>(first, last, last,
				(BfmeScoreEntry *)0, comp);
			return;
		}
		--depthLimit;
		BfmeScoreEntryLess medianComp;
		BfmeScoreEntry *cut = _STL::__unguarded_partition(
			first, last,
			*BfmeScoreEntryMedian00575450(first,
				first + (last - first) / 2, last - 1, medianComp), comp);
		Gen00575450(cut, last,
			(BfmeScoreEntry *)0, depthLimit, comp);
		last = cut;
	}
}
