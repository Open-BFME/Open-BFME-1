// cl: /Od
// Open-BFME5 conversions.

extern void *g_bfmeSinkSTA;

// Defines bfmeFormatToBuffer88A640 (RVA 0x88A640), matched in
// game/GameEngine/Source/Common/BfmeFormatBuffer88A640.cpp.
void bfmeFormatToBuffer88A640(const char *format, ...);
void bfmeFlushSTA(void);

void bfmeGoSTA(int a, int b, int c)
{
	bfmeFormatToBuffer88A640((const char *)g_bfmeSinkSTA, b, c, a);
	bfmeFlushSTA();
}
