// Open-BFME5 conversions.

extern char g_bfmeOneSJA[];
extern char g_bfmeTwoSJA[];
extern char g_bfmeDoneSJA;

void bfmeReadSJA(void *slot, void *p, char *out);
void bfmeLoadSJA(void *slot, void *p, char *out);

void bfmeGoSJA(void *p)
{
	char v;
	bfmeReadSJA(g_bfmeOneSJA, p, &v);
	bfmeLoadSJA(g_bfmeTwoSJA, p, &v);
	g_bfmeDoneSJA = 0;
}
