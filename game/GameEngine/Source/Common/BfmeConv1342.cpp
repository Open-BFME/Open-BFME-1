// Open-BFME5 conversions.

struct Rva009B4680State;

int Rva009B4680Normalize(Rva009B4680State *state);

int bfmeGoUSC(void *p, int n)
{
	int r = 0;
	for (int i = n - 1; i >= 0; --i)
		r |= Rva009B4680Normalize((Rva009B4680State *)p) << i;
	return r;
}
