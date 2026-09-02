// Open-BFME5 conversions.

void bfmeStepVOZ(void *a, void *b, int n, void *c);

void bfmeSortVOZ(void *a, void *b, void *c)
{
	char *p = (char *)b;
	int d = (int)(p - (char *)a);

	while (d / 12 > 1)
	{
		bfmeStepVOZ(a, p, 0, c);
		d -= 12;
		p -= 12;
	}
}
