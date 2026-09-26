// cl: /Od /Gy
// Open-BFME5 conversions.

extern void *g_bfmeTableSXA[];

void bfmeWriteSXA(void *sink, ...);
void bfmeFlushSXA(void);

void bfmeGoSXA(int a, int b, int c, int d)
{
	bfmeWriteSXA(g_bfmeTableSXA[2], c, d, g_bfmeTableSXA[b], c, d, a);
	bfmeFlushSXA();
}
