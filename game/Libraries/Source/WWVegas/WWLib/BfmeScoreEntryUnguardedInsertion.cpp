// cl: /DNDEBUG /MD /EHsc

// Retail 0x005742C0 is the STLport unguarded insertion pass for the
// BfmeScoreEntry sort family. The caller family and Rva00573980 establish the
// record and comparator types.

struct BfmeScoreEntry
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

struct BfmeScoreEntryLess
{
	bool operator()(const BfmeScoreEntry *left,
		const BfmeScoreEntry *right) const;
};

namespace _STL
{

void Rva00573980(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntry value, BfmeScoreEntryLess comp);

}

// ?Rva005742C0@@YAXPAUBfmeScoreEntry@@0UBfmeScoreEntryLess@@@Z
void Rva005742C0(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntryLess comp)
{
	if (first != last)
	{
		BfmeScoreEntry *i = first + 1;
		if (i != last)
		{
			do
			{
				_STL::Rva00573980(first, i, *i, comp);
				++i;
			}
			while (i != last);
		}
	}
}
