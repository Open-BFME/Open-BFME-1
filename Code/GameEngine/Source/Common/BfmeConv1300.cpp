// cl: /Od
// Open-BFME5 conversions.

extern void *g_bfmeSinkSTA;

void bfmeWriteSTA(void *sink, int a, int b, int c);
void bfmeFlushSTA(void);

void bfmeGoSTA(int a, int b, int c)
{
	bfmeWriteSTA(g_bfmeSinkSTA, b, c, a);
	bfmeFlushSTA();
}
