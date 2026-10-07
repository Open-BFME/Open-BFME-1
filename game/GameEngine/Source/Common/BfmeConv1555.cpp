// Open-BFME5 conversions.

// ILT 0x3CEED -> 0x00531D80, matched ?gen00531D80@@YAXPAX0H0@Z
// (S4PopHeapAuxElem12.cpp), same signature.
void gen00531D80(void *a, void *b, int n, void *c);
static inline void bfmeStepVOY(void *a, void *b, int n, void *c) { gen00531D80(a, b, n, c); }

void bfmeSortVOY(void *a, void *b, void *c)
{
	char *p = (char *)b;
	int d = (int)(p - (char *)a);

	while (d / 12 > 1)
	{
		bfmeStepVOY(a, p, 0, c);
		d -= 12;
		p -= 12;
	}
}
