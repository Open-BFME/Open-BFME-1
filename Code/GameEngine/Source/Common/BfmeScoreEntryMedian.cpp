// cl: /DNDEBUG /MD /EHsc

struct BfmeScoreEntry
{
	int m_words[4];
};

struct BfmeScoreEntryLess
{
	bool operator()(const BfmeScoreEntry *left,
		const BfmeScoreEntry *right) const;
};

extern "C" BfmeScoreEntry *Rva00570AC0(
	BfmeScoreEntry *a,
	BfmeScoreEntry *b,
	BfmeScoreEntry *c,
	BfmeScoreEntryLess comp)
{
	if (comp(a, b))
		if (comp(b, c))
			return b;
		else if (comp(a, c))
			return c;
		else
			return a;
	else if (comp(a, c))
		return a;
	else if (comp(b, c))
		return c;
	else
		return b;
}
