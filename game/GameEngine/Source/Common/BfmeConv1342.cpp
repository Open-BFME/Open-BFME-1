// Open-BFME5 conversions.

int bfmeNormUSC(void *p);

int bfmeGoUSC(void *p, int n)
{
	int r = 0;
	for (int i = n - 1; i >= 0; --i)
		r |= bfmeNormUSC(p) << i;
	return r;
}
