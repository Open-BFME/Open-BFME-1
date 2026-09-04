// ?bfmeSortInt005336D0@@YAXPAH0US4Cmp005336D0@@@Z
// partial score=0.94 date=2026-09-04
// ?bfmeSortInt005336D0@@YAXPAH0US4Cmp005336D0@@@Z
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport sort over a four-byte element, retail 0x005336D0,
// 109 bytes.  The log2 countdown is STLport's __lg; the 0x40 threshold is
// sixteen 4-byte elements.  Helpers are out of line.

struct S4Cmp005336D0
{
	void *m_bfmeState;
	bool operator()(int, int) const;
};

void bfmeIntrosortLoop005336D0(int *first, int *last, int *, int depth,
	S4Cmp005336D0 comp);
void bfmeInsertionSort005336D0(int *first, int *last, S4Cmp005336D0 comp);
void bfmeUnguardedInsertionSort005336D0(int *first, int *last,
	S4Cmp005336D0 comp);

void bfmeSortInt005336D0(int *first, int *last, S4Cmp005336D0 comp)
{
	if (first == last)
		return;
	int n = last - first;
	int x = n;
	int lg = 0;
	if (x != 1)
	{
		do
		{
			x >>= 1;
			++lg;
		} while (x != 1);
	}
	bfmeIntrosortLoop005336D0(first, last, 0, lg * 2, comp);
	if (n > 16)
	{
		bfmeInsertionSort005336D0(first, first + 16, comp);
		bfmeUnguardedInsertionSort005336D0(first + 16, last, comp);
	}
	else
		bfmeInsertionSort005336D0(first, last, comp);
}
