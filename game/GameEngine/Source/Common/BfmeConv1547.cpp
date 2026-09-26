// Open-BFME5 conversions.

void bfmeStepVOU(void *a, void *b, int n, void *c);

void bfmeSortVOU(void *a, void *b, void *c)
{
	char *p = (char *)b;
	int d = (int)(p - (char *)a);

	while ((d & ~3) > 4)
	{
		bfmeStepVOU(a, p, 0, c);
		d -= 4;
		p -= 4;
	}
}
