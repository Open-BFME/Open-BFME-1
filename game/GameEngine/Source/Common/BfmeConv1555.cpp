// Open-BFME5 conversions.

void bfmeStepVOY(void *a, void *b, int n, void *c);

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
