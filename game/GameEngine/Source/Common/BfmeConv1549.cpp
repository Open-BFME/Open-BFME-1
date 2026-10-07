// Open-BFME5 conversions.

// Retail 0x00476250 calls ILT 0x2F329 -> matched 0x00474A90 (callees.py).
struct Rva004748F0Element;

struct Rva004748F0Compare
{
	int m_state;
};

void Rva00474A90PopHeapAux(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *, Rva004748F0Compare comp);

static __forceinline void bfmeStepVOV(void *a, void *b, int n, void *c)
{
	Rva00474A90PopHeapAux((Rva004748F0Element *)a, (Rva004748F0Element *)b,
		(Rva004748F0Element *)n, *(Rva004748F0Compare *)&c);
}

void bfmeSortVOV(void *a, void *b, void *c)
{
	char *p = (char *)b;
	int d = (int)(p - (char *)a);

	while ((d & ~0xf) > 0x10)
	{
		bfmeStepVOV(a, p, 0, c);
		d -= 0x10;
		p -= 0x10;
	}
}
