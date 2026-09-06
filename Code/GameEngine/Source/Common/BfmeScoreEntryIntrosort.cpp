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

extern BfmeScoreEntry *BfmeScoreEntryPartition005724D0(
	BfmeScoreEntry *, BfmeScoreEntry *, BfmeScoreEntry,
	BfmeScoreEntryLess);
extern void BfmeScoreEntryPartialSort00574410(
	BfmeScoreEntry *, BfmeScoreEntry *, BfmeScoreEntry *, int,
	BfmeScoreEntryLess);
extern void BfmeScoreEntryIntrosortSelf00575450(
	BfmeScoreEntry *, BfmeScoreEntry *, BfmeScoreEntry *, int,
	BfmeScoreEntryLess);

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
			BfmeScoreEntryPartialSort00574410(first, last, last, 0, comp);
			return;
		}
		--depthLimit;
		BfmeScoreEntryLess medianComp;
		BfmeScoreEntry *cut = BfmeScoreEntryPartition005724D0(
			first, last,
			*BfmeScoreEntryMedian00575450(first,
				first + (last - first) / 2, last - 1, medianComp), comp);
		BfmeScoreEntryIntrosortSelf00575450(cut, last,
			(BfmeScoreEntry *)0, depthLimit, comp);
		last = cut;
	}
}
