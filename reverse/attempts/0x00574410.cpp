// cl: /DNDEBUG /MD /EHsc
// partial score=0.995 date=2026-09-11

// Open-BFME5: STLport partial_sort over the 16-byte score-screen record.
// Gen00575450 calls this helper through ILT 0x00037B5F when introsort reaches
// its depth limit.  The make-heap, adjust-heap, comparator, and sort-heap
// callees match the existing score-entry specializations.

struct BfmeScoreEntry
{
	int m_words[4];
};

struct BfmeScoreEntryLess
{
	bool operator()(const BfmeScoreEntry *left,
		const BfmeScoreEntry *right) const;
};

void b_005727e0();
void b_0000ce0a();
void b_00573b00();

typedef void (__cdecl *BfmeScoreEntryMakeHeap)(
	void *, void *, void *, int, int);
typedef void (__cdecl *BfmeScoreEntryAdjustHeap)(
	BfmeScoreEntry *, int, int, BfmeScoreEntry, void *);
typedef void (__cdecl *BfmeScoreEntrySortHeap)(void *, void *, void *);

// ?BfmeScoreEntryPartialSort00574410@@YAXPAX00H0@Z
void BfmeScoreEntryPartialSort00574410(void *firstArgument,
	void *middleArgument, void *lastArgument, int, void *compareArgument)
{
	BfmeScoreEntry *first = (BfmeScoreEntry *)firstArgument;
	BfmeScoreEntry *middle = (BfmeScoreEntry *)middleArgument;
	BfmeScoreEntry *last = (BfmeScoreEntry *)lastArgument;

	((BfmeScoreEntryMakeHeap)b_005727e0)(first, middle,
		compareArgument, 0, 0);
	const BfmeScoreEntryLess compare =
		*(BfmeScoreEntryLess *)compareArgument;
	for (BfmeScoreEntry *i = middle; i < last; ++i)
	{
		if (compare.operator()(i, first))
		{
			BfmeScoreEntry value = *i;
			*i = *first;
			((BfmeScoreEntryAdjustHeap)b_0000ce0a)(first, 0,
				(int)(middle - first), value, compareArgument);
		}
	}
	((BfmeScoreEntrySortHeap)b_00573b00)(first, middle,
		compareArgument);
}
