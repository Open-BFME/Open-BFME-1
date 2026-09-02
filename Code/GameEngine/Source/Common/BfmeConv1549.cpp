// Open-BFME5 conversions.

void bfmeStepVOV(void *a, void *b, int n, void *c);

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
