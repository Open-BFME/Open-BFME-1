// cl: /Od /Gy
// Open-BFME5 conversions.

extern void *g_bfmeTableSXA[];

// Defines bfmeFormatToBuffer88A640 (RVA 0x88A640), matched in
// game/GameEngine/Source/Common/BfmeFormatBuffer88A640.cpp.
void bfmeFormatToBuffer88A640(const char *format, ...);
void bfmeFlushSXA(void);

void bfmeGoSXA(int a, int b, int c, int d)
{
	bfmeFormatToBuffer88A640((const char *)g_bfmeTableSXA[2], c, d, g_bfmeTableSXA[b], c, d, a);
	bfmeFlushSXA();
}
